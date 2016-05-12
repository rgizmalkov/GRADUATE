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
	double jd;

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
	void setJD(double val) { this->jd = val; }
	//getters
	int getId() { return this->id; };
	double getRX() { return this->rx; }
	double getRY() { return this->ry; }
	double getRZ() { return this->rz; }
	double getVX() { return this->vx; }
	double getVY() { return this->vy; }
	double getVZ() { return this->vz; }
	double getJD() { return this->jd; }
	void getR(double val[3]) { val[0] = rx;val[1] = ry;val[2] = rz; }
	void getV(double val[3]) { val[0] = vx;val[1] = vy;val[2] = vz; }


};

