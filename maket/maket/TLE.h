#pragma once
#include "Entity.h"
#include "MySQL.h"
#include <string>
using namespace std;
class TLE : Entity
{
private:
	MySQL* sql;

	int id;

	/* first line */
	std::string _numberOfLine1;
	std::string _satelliteNumbers1;//NORAD

	std::string _classification;
	std::string _internationalDesignatorYear;
	std::string _internationalDesignator;
	std::string _piece;
	std::string _epochYear;
	std::string _epochTime;
	std::string _meanMotionDerivative;
	std::string _meanMotionSecondDerivative;
	std::string  _averageAcceleration;
	std::string _typeOfEphemeris;
	std::string _elementsNumber;
	std::string _chkSum;

	/* second line */
	std::string _numberOfLine2;
	std::string _satelliteNumbers2;
	std::string _inclination;
	std::string _rightAscensionOfTheNode;
	std::string _eccentricity;
	std::string _argOfPerigee;
	std::string _meanAnomaly;
	std::string _meanMotion;
	std::string _epochRev;
	std::string _chk;

	static const string DROP_TLE;
public:
	TLE();
	~TLE();
	//methods
	Entity* loadEntity(MYSQL_ROW row);
	void saveEntity();
	void dropEntity();
	void updateEntity();
	string toString();
	//setters
	void setId(int id) { this->id = id; };
	void set_numberOfLine1(std::string _numberOfLine1) { this->_numberOfLine1 = _numberOfLine1; };
	void set_satelliteNumbers1(std::string _satelliteNumbers1) { this->_satelliteNumbers1 = _satelliteNumbers1; };
	void set_classification(std::string _classification) { this->_classification = _classification; };
	void set_internationalDesignatorYear(std::string _internationalDesignatorYear) { this->_internationalDesignatorYear = _internationalDesignatorYear; };
	void set_internationalDesignator(std::string _internationalDesignator) { this->_internationalDesignator = _internationalDesignator; };
	void set_piece(std::string _piece) { this->_piece = _piece; };
	void set_epochYear(std::string _epochYear) { this->_epochYear = _epochYear; };
	void set_epochTime(std::string _epochTime) { this->_epochTime = _epochTime; };
	void set_meanMotionDerivative(std::string _meanMotionDerivative) { this->_meanMotionDerivative = _meanMotionDerivative; };
	void set_meanMotionSecondDerivative(std::string _meanMotionSecondDerivative) { this->_meanMotionSecondDerivative = _meanMotionSecondDerivative; };
	void set_averageAcceleration(std::string _averageAcceleration) { this->_averageAcceleration = _averageAcceleration; };
	void set_typeOfEphemeris(std::string _typeOfEphemeris) { this->_typeOfEphemeris = _typeOfEphemeris; };
	void set_elementsNumber(std::string _elementsNumber) { this->_elementsNumber = _elementsNumber; };
	void set_chkSum(std::string _chk) { this->_chk = _chk; };
	void set_numberOfLine2(std::string _numberOfLine2) { this->_numberOfLine2 = _numberOfLine2; };
	void set_satelliteNumbers2(std::string _satelliteNumbers2) { this->_satelliteNumbers2 = _satelliteNumbers2; };
	void set_inclination(std::string _inclination) { this->_inclination = _inclination; };
	void set_rightAscensionOfTheNode(std::string _rightAscensionOfTheNode) { this->_rightAscensionOfTheNode = _rightAscensionOfTheNode; };
	void set_eccentricity(std::string _eccentricity) { this->_eccentricity = _eccentricity; };
	void set_argOfPerigee(std::string _argOfPerigee) { this->_argOfPerigee = _argOfPerigee; };
	void set_meanAnomaly(std::string _meanAnomaly) { this->_meanAnomaly = _meanAnomaly; };
	void set_meanMotion(std::string _meanMotion) { this->_meanMotion = _meanMotion; };
	void setEpochRev(std::string _epochRev) { this->_epochRev = _epochRev; };
	void set_chk(std::string _chk) { this->_chk = _chk; };
	//getters
	int getId() { return this->id; };
	vector<string> getVars();
};

