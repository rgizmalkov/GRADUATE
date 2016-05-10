#include "Satellite.h"
const string Satellite::DROP_SAT = "DELETE * FROM SAT WHERE ID = ";
const string Satellite::GET_STATE = "SELECT * FROM STATE WHERE ID = ";
const string Satellite::GET_KEP = "SELECT * FROM KEP WHERE ID = ";
const string Satellite::GET_TLE = "SELECT * FROM TLE WHERE ID = ";


Satellite::Satellite() {
	sql = MySQL::newInstanse();
}
Satellite::~Satellite()
{
	delete tle;
	delete state;
	delete kep;
}

Entity* Satellite::loadEntity(MYSQL_ROW row) {
	MYSQL_ROW vrow;

	int i = 0;
	std::string step = row[i++];
	this->setId(stoi(step));
	step = row[i++];
	this->setRealDate(step);
	step = row[i++];
	this->setExchangedDate(step);
	if (row[i] != NULL) {
		step = row[i];
		this->setTypeOfSatellite(step);
	}
	i++;
	if (row[i] != NULL) {
		step = row[i];
		KeplerianElements* vkep = new KeplerianElements();
		this->kep = (KeplerianElements*) vkep->loadEntity(vrow =  mysql_fetch_row(sql->execute(GET_KEP + step)));
	}
	i++;
	if (row[i] != NULL) {
		step = row[i];
		State* vstate = new State();
		this->state = (State*)vstate->loadEntity(vrow = mysql_fetch_row(sql->execute(GET_STATE + step)));
	}
	i++;
	if (row[i] != NULL) {
		step = row[i];
		TLE* vtle = new TLE();
		this->tle = (TLE*)vtle->loadEntity(vrow = mysql_fetch_row(sql->execute(GET_TLE + step)));
	}
	return this;
}

void Satellite::saveEntity() {
	string format = "INSERT INTO SAT (ID, EXCHANGEDDATE, REALDATE";
	if (!typeOfSatellites.empty()) format += ", TYPEOFSATELLITE";

	bool bkep = false;
	bool bstate = false;
	bool btle = false;
	if (bkep != NULL) { bkep = true; format += ", KEP"; }
	if (bstate != NULL) { bstate = true; format += ", STATE";}
	if (tle != NULL) { btle = true; format += ", TLE"; }
	format += ")"; format += "VALUES"; format += "(" + std::to_string(id) + ", '" + exchangedDate + "','" + realDate + "'";
	if (!typeOfSatellites.empty()) format += ", '" + typeOfSatellites + "'";
	if (bkep) { format += ", '" + to_string(kep->getId()) + "'"; kep->saveEntity(); }
	if (bstate) { format += ", '" + to_string(state->getId()) + "'"; state->saveEntity(); }
	if (btle) { format += ", '" + to_string(tle->getId()) + "'"; tle->saveEntity(); }
	format += ");";
	sql->query(format);
}

void Satellite::dropEntity() {
	string format = DROP_SAT + to_string(this->id);
	sql->query(format);
};

void Satellite::updateEntity() {
	string format = "UPDATE KEP SAT ";
	format += "realDate = '" + realDate + "'";
	format += ", exchangedDate = '" + exchangedDate + "'";
	if (!typeOfSatellites.empty()) format += ", typeOfSatellites = '" + typeOfSatellites + "'";
	if (kep != NULL) kep->updateEntity();
	if (state != NULL) state->updateEntity();
	if (tle != NULL) tle->updateEntity();
	format += " WHERE ID = " + to_string(this->id);
	sql->query(format);
};

string Satellite::toString() {
	string ret = "Satellite (" + to_string(id) + ")\r\n";
	ret += "date: " + realDate + " (before: " + exchangedDate + ")\r\n";
	if (!typeOfSatellites.empty()) ret += "type: " + typeOfSatellites + "\r\n";
	if (state != NULL) ret += state->toString();
	if (tle != NULL) ret += tle->toString();
	if (kep != NULL) ret += kep->toString();
	return ret;
}
