#pragma once
#include "Entity.h"
#include "MySQL.h"
#include <string>
using namespace std;
class KeplerianElements : Entity
{
private:
	MySQL* sql;

	int id;

	double a;
	double e;
	double i;
	double q;
	double w;
	double o;

	static const string DROP_KEP;
public:
	KeplerianElements();
	~KeplerianElements();
	//methods
	Entity* loadEntity(MYSQL_ROW row);
	void saveEntity();
	void dropEntity();
	void updateEntity();
	string toString();
	//setters
	void setId(int id) { this->id = id; };
	void setA(double val) { this->a = val; }
	void setE(double val) { this->e = val; }
	void setI(double val) { this->i = val; }
	void setQ(double val) { this->q = val; }
	void setW(double val) { this->w = val; }
	void setO(double val) { this->o = val; }
	//getters
	int getId() { return this->id; };
	double getA() { return this->a; }
	double getE() { return this->e; }
	double getI() { return this->i; }
	double getQ() { return this->q; }
	double getW() { return this->w; }
	double getO() { return this->o; }
};

