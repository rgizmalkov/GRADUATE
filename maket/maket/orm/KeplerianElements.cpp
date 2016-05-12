#include "KeplerianElements.h"
const string KeplerianElements::DROP_KEP = "DELETE * FROM KEP WHERE ID = ";


KeplerianElements::KeplerianElements()
{
	sql = MySQL::newInstanse();
}


KeplerianElements::~KeplerianElements()
{
}

Entity* KeplerianElements::loadEntity(MYSQL_ROW row) {
	int i = 0;
	std::string step = row[i++];
	this->setId(stoi(step));
	step = row[i++];
	this->setA(stod(step));
	step = row[i++];
	this->setE(stod(step));
	step = row[i++];
	this->setI(stod(step));
	step = row[i++];
	this->setO(stod(step));
	step = row[i++];
	this->setQ(stod(step));
	step = row[i];
	this->setW(stod(step));
	return this;
}

void KeplerianElements::saveEntity() {
	string format = "INSERT INTO STATE (ID,A,E,I,Q,W,O) VALUES (" +
		to_string(id) + ", " +
		to_string(a) + ", " +
		to_string(e) + ", " +
		to_string(i) + ", " +
		to_string(q) + ", " +
		to_string(w) + ", " +
		to_string(o) + ")";
	sql->query(format);
}

void KeplerianElements::dropEntity() {
	string format = DROP_KEP + to_string(this->id);
	sql->query(format);
};

void KeplerianElements::updateEntity() {
	string format = "UPDATE KEP SET ";
	format += "A = " + to_string(a);
	format += "E = " + to_string(e);
	format += "I = " + to_string(i);
	format += "Q = " + to_string(q);
	format += "W = " + to_string(w);
	format += "O = " + to_string(q);
	format += " WHERE ID = " + to_string(this->id);
	sql->query(format);
};

string KeplerianElements::toString() {
	string ret = "KeplerianElements (" + to_string(id) + ")\r\n";
	ret += "a= " + to_string(a) + ", e= " + to_string(e) + ", i= " + to_string(i) + ")\r\n";
	ret += "q= " + to_string(q) + ", w= " + to_string(w) + ", o= " + to_string(o) + ")\r\n";
	return ret;
}
