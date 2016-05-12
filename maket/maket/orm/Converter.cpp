#include "Converter.h"
#include "../sgp4v/SGP4V.h"
#include "../sgp4v/add_func.h"
#include "../handlers/Date.h"
#include "MySQL.h"
Date getDate(int id);

Converter::Converter()
{
}


Converter::~Converter()
{
}

State Converter::tleToState(TLE tle) {
	State state;
	double kep_jul[7]; 
	jsgp4v(tle.getLine1(), tle.getLine2(), kep_jul);
	state.setRX(kep_jul[0]);
	state.setRY(kep_jul[1]);
	state.setRZ(kep_jul[2]);
	state.setVX(kep_jul[3]);
	state.setVY(kep_jul[4]);
	state.setVZ(kep_jul[5]);
	state.setJD(kep_jul[6]);
	state.setId(tle.getId());
	return state;
};
KeplerianElements Converter::stateToKep(State state) {
	KeplerianElements kep;
	double kep_in[] = { state.getRX(), state.getRY(), state.getRZ(), state.getVX(), state.getVY(), state.getVZ() };
	double a, e, i, q, w, o;
	CoordsToElements(kep_in, a, e, i, q, w, o);
	kep.setA(a);
	kep.setE(e);
	kep.setI(i);
	kep.setQ(q);
	kep.setW(w);
	kep.setO(o);
	kep.setId(kep.getId());
	return kep;
};
Satellite Converter::satFromTle(TLE tle) {
	int id = tle.getId();
	bool isExist = Satellite::isEntityExist(id);
	State state = tleToState(tle);
	KeplerianElements kep = stateToKep(state);
	Satellite sat;
	sat.setId(id);
	sat.setKep(&kep);
	sat.setState(&state);
	sat.setTle(&tle);
	if (isExist) {
		Date date = getDate(id);
		Date rdate(state.getJD());
		sat.setExchangedDate(date.getSTime());
		sat.setRealDate(rdate.getSTime());
	}
	else {
		Date rdate(state.getJD());
		sat.setExchangedDate(rdate.getSTime());
		sat.setRealDate(rdate.getSTime());
	}
	return sat;
};
Satellite Converter::satFromState(State state) {
	int id = state.getId();
	bool isExist = Satellite::isEntityExist(id);
	KeplerianElements kep = stateToKep(state);
	Satellite sat;
	sat.setId(id);
	sat.setKep(&kep);
	sat.setState(&state);
	if (isExist) {
		Date date = getDate(id);
		Date rdate(state.getJD());
		sat.setExchangedDate(date.getSTime());
		sat.setRealDate(rdate.getSTime());
	}
	else {
		Date rdate(state.getJD());
		sat.setExchangedDate(rdate.getSTime());
		sat.setRealDate(rdate.getSTime());
	}
	return sat;
};

Date getDate(int id) {
	MySQL* sql = MySQL::newInstanse();
	MYSQL_RES * results = sql->execute("SELECT EXCHANGEDDATE FROM SAT WHERE ID = " + to_string(id));
	MYSQL_ROW row = mysql_fetch_row(results);
	string d = row[0];
	Date date(d, Date::DB_FORMAT);
	return date;
}