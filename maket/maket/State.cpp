#include "State.h"
const string State::DROP_STATE = "DELETE * FROM STATE WHERE ID = ";


State::State()
{
	sql = MySQL::newInstanse();
}


State::~State()
{
}

Entity* State::loadEntity(MYSQL_ROW row) {
	int i = 0;
	std::string step = row[i++];
	this->setId(stoi(step));
	step = row[i++];
	this->setRX(stod(step));
	step = row[i++];
	this->setRY(stod(step));
	step = row[i++];
	this->setRZ(stod(step));
	step = row[i++];
	this->setVX(stod(step));
	step = row[i++];
	this->setVY(stod(step));
	step = row[i];
	this->setVZ(stod(step));
	return this;
}

void State::saveEntity() {
	string format = "INSERT INTO STATE (ID,RX,RY,RZ,VX,VY,VZ) VALUES (" + 
		to_string(id) + ", " + 
		to_string(rx) + ", " +
		to_string(ry) + ", " +
		to_string(rz) + ", " +
		to_string(vx) + ", " +
		to_string(vy) + ", " +
		to_string(vz) + ")";
	sql->query(format);
}

void State::dropEntity() {
	string format = DROP_STATE + to_string(this->id);
	sql->query(format);
};
void State::updateEntity() {
	string format = "UPDATE KEP SET ";
	format += "RX = " + to_string(rx);
	format += "RY = " + to_string(ry);
	format += "RZ = " + to_string(rz);
	format += "VX = " + to_string(vx);
	format += "VY = " + to_string(vy);
	format += "VZ = " + to_string(vz);
	format += " WHERE ID = " + to_string(this->id);
	sql->query(format);
};

string State::toString() {
	string ret = "State (" + to_string(id) + ")\r\n";
	ret += "R(" + to_string(rx) + ", " + to_string(ry) + ", " + to_string(rz) + ")\r\n";
	ret += "V(" + to_string(vx) + ", " + to_string(vy) + ", " + to_string(vz) + ")\r\n";
	return ret;
}