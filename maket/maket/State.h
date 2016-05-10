#pragma once
#include "Entity.h"
#include "MySQL.h"
#include <string>
using namespace std;
class State : Entity
{
private:
	MySQL* sql;

	int id;

	double rx;
	double ry;
	double rz;
	double vx;
	double vy;
	double vz;

	static const string DROP_STATE;
public:
	State();
	~State();
	//methods
	Entity* loadEntity(MYSQL_ROW row);
	void saveEntity();
	void dropEntity();
	void updateEntity();
	string toString();
	//setters
	void setId(int id) { this->id = id; };
	void setRX(double val) { this->rx = val; }
	void setRY(double val) { this->ry = val; }
	void setRZ(double val) { this->rz = val; }
	void setVX(double val) { this->vx = val; }
	void setVY(double val) { this->vy = val; }
	void setVZ(double val) { this->vz = val; }
	//getters
	int getId() { return this->id; };
	double getRX() { return this->rx; }
	double getRY() { return this->ry; }
	double getRZ() { return this->rz; }
	double getVX() { return this->vx; }
	double getVY() { return this->vy; }
	double getVZ() { return this->vz; }



};

