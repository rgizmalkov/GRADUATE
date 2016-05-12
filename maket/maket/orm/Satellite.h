#pragma once
#include "Entity.h"
#include "State.h"
#include "TLE.h"
#include "KeplerianElements.h"
#include "MySQL.h"
#include <string>
using namespace std;

class Satellite : public Entity
{
private:
	//query strings
	static const string GET_STATE;
	static const string GET_KEP;
	static const string GET_TLE;
	static const string DROP_SAT;
	//variables
	MySQL* sql;
	//***
	int id;

	string realDate;
	string exchangedDate;
	string typeOfSatellites;

	State* state;
	TLE* tle;
	KeplerianElements* kep;
public:
	//constructors and destructors
	Satellite();
	~Satellite();
	//methods
	Entity* loadEntity(MYSQL_ROW row);
	void saveEntity();
	void dropEntity();
	void updateEntity();
	static int isEntityExist(int id);
	//setters
	void setId(int id) { this->id = id; };
	void setRealDate(string time) { this->realDate = time; };
	void setExchangedDate(string time) { this->exchangedDate = time; };
	void setTypeOfSatellite(string desc) { this->typeOfSatellites = desc; };
	void setKep(KeplerianElements* kep) { this->kep = kep; };
	void setState(State* state) { this->state = state; };
	void setTle(TLE* tle) { this->tle = tle; };
	//getters
	int getId() { return this->id; };
	string getRealDate() { return this->realDate; };
	string getExchangedDate() { return this->exchangedDate; };
	string getTypeOfSatellite() { return this->typeOfSatellites; };
	State* getState() { return this->state; }
	TLE* getTle() { return this->tle; }
	KeplerianElements* getKep() { return this->kep; }

	string toString();
};

