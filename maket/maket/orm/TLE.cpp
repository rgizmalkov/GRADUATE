#include "TLE.h"
const string TLE::DROP_TLE = "DELETE * FROM TLE WHERE ID = ";
void putInLine(std::string ch, int from, int to, int size, string& _line);


TLE::TLE()
{
	sql = MySQL::newInstanse();
}
TLE::TLE(std::string line1, std::string line2) {
	

	_numberOfLine1 = line1.substr(0, 1);
	_satelliteNumbers1 = line1.substr(2, 5);
	_classification = line1.substr(7, 1);
	_internationalDesignatorYear = line1.substr(9, 2);
	_internationalDesignator = line1.substr(11, 3);
	_piece = line1.substr(14, 3);
	_epochYear = line1.substr(18, 2);
	_epochTime = line1.substr(20, 12);
	_meanMotionDerivative = line1.substr(33, 10);
	_meanMotionSecondDerivative = line1.substr(44, 8);
	_averageAcceleration = line1.substr(53, 8);
	_typeOfEphemeris = line1.substr(62, 1);
	_elementsNumber = line1.substr(64, 4);
	_chkSum = line1.substr(68, 1);

	_numberOfLine2 = line2.substr(0, 1);
	_satelliteNumbers2 = line2.substr(2, 5);
	_inclination = line2.substr(8, 8);
	_rightAscensionOfTheNode = line2.substr(17, 8);
	_eccentricity = line2.substr(26, 7);
	_argOfPerigee = line2.substr(34, 8);
	_meanAnomaly = line2.substr(43, 8);
	_meanMotion = line2.substr(52, 11);
	_epochRev = line2.substr(63, 5);
	_chk = line2.substr(68, 1);

	id = stoi(_satelliteNumbers1);
}


TLE::~TLE()
{
}
Entity* TLE::loadEntity(MYSQL_ROW row) {
	int i = 0;
	std::string step = row[i++];	this->setId(stoi(step));
	step = row[i++];				this->set_argOfPerigee(step);
	step = row[i++];				this->set_averageAcceleration(step);
	step = row[i++];				this->set_chk(step);
	step = row[i++];				this->set_chkSum(step);
	step = row[i++];				this->set_classification(step);
	step = row[i++];				this->set_eccentricity(step);
	step = row[i++];				this->set_elementsNumber(step);
	step = row[i++];				this->set_epochTime(step);
	step = row[i++];				this->set_epochYear(step);
	step = row[i++];				this->set_inclination(step);
	step = row[i++];				this->set_internationalDesignator(step);
	step = row[i++];				this->set_internationalDesignatorYear(step);
	step = row[i++];				this->set_meanAnomaly(step);
	step = row[i++];				this->set_meanMotion(step);
	step = row[i++];				this->set_meanMotionDerivative(step);
	step = row[i++];				this->set_meanMotionSecondDerivative(step);
	step = row[i++];				this->set_numberOfLine1(step);
	step = row[i++];				this->set_numberOfLine2(step);
	step = row[i++];				this->set_piece(step);
	step = row[i++];				this->set_rightAscensionOfTheNode(step);
	step = row[i++];				this->set_satelliteNumbers1(step);
	step = row[i++];				this->set_satelliteNumbers2(step);
	step = row[i++];				this->set_typeOfEphemeris(step);
	step = row[i];					this->setEpochRev(step);
	return this;
}

void TLE::saveEntity() {
	vector<string> tle_el = getVars();
	string format = "INSERT INTO orbitcomponents2 (ID, _numberOfLine1,  _satelliteNumbers1, _classification, _internationalDesignatorYear,\
	_internationalDesignator, _piece, _epochYear, _epochTime, _meanMotionDerivative, _meanMotionSecondDerivative, _averageAcceleration,_typeOfEphemeris, _elementsNumber, \
	_chkSum, _numberOfLine2,  _satelliteNumbers2, _inclination, _rightAscensionOfTheNode, _eccentricity, _argOfPerigee,_meanAnomaly,_meanMotion, \
	epochRev, _chk) VALUES (" + std::to_string(id) + ", '" + tle_el[0] + "','" + tle_el[1] + "','" + tle_el[2] + "','" + tle_el[3] + "','\
	" + tle_el[4] + "','" + tle_el[5] + "','" + tle_el[6] + "','" + tle_el[7] + "','" + tle_el[8] + "','" + tle_el[9] + "','" + tle_el[10] + "','" + tle_el[11] + "','" + tle_el[12] + "','\
	" + tle_el[13] + "','" + tle_el[14] + "','" + tle_el[15] + "','" + tle_el[16] + "','" + tle_el[17] + "','" + tle_el[18] + "','" + tle_el[19] + "','" + tle_el[20] + "','" + tle_el[21] + "','\
	" + tle_el[22] + "','" + tle_el[23] + "');"; 
	sql->query(format);
}

void TLE::dropEntity() {
	string format = DROP_TLE + to_string(this->id);
	sql->query(format);
};
void TLE::updateEntity() {
	vector<string> tle_el = getVars();
	string format = "UPDATE TLE SET ";
	format += " _classification = '" + tle_el[2] + "', ";
	format += " _internationalDesignatorYear = '" + tle_el[3] + "', ";
	format += "_internationalDesignator = '" + tle_el[4] + "', ";
	format += "_piece = '" + tle_el[5] + "', ";
	format += "_epochYear = '" + tle_el[6] + "', ";
	format += "_epochTime = '" + tle_el[7] + "', ";
	format += " _meanMotionDerivative = '" + tle_el[8] + "', ";
	format += "_meanMotionSecondDerivative = '" + tle_el[9] + "', ";
	format += "_averageAcceleration = '" + tle_el[10] + "', ";
	format += "_typeOfEphemeris = '" + tle_el[11] + "', ";
	format += "_elementsNumber = '" + tle_el[12] + "', ";
	format += "_chkSum = '" + tle_el[13] + "', ";
	format += "_inclination = '" + tle_el[17] + "', ";
	format += "_rightAscensionOfTheNode = '" + tle_el[18] + "', ";
	format += "_eccentricity = '" + tle_el[19] + "', ";
	format += "_argOfPerigee = '" + tle_el[20] + "', ";
	format += "_meanAnomaly = '" + tle_el[21] + "', ";
	format += "_meanMotion = '" + tle_el[22] + "', ";
	format += "epochRev = '" + tle_el[22] + "', ";
	format += "_chk = '" + tle_el[23] + "'";
	format += " WHERE ID = " + to_string(this->id);
	sql->query(format);
};

std::vector<std::string> TLE::getVars() {
	std::vector<std::string> str = { _numberOfLine1, _satelliteNumbers1, _classification, _internationalDesignatorYear, _internationalDesignator,
		_piece, _epochYear, _epochTime, _meanMotionDerivative, _meanMotionSecondDerivative, _averageAcceleration, _typeOfEphemeris,
		_elementsNumber, _chkSum, _numberOfLine2, _satelliteNumbers2, _inclination, _rightAscensionOfTheNode, _eccentricity, _argOfPerigee,
		_meanAnomaly, _meanMotion, _epochRev, _chk };
	return str;
}

string TLE::toString() {
	string _line1 = "                                                                     ";
	putInLine(_numberOfLine1, 0, 1, _numberOfLine1.length(), _line1);
	putInLine(_satelliteNumbers1, 2, 7, _satelliteNumbers1.length(), _line1);
	putInLine(_classification, 7, 8, _classification.length(), _line1);
	putInLine(_internationalDesignatorYear, 9, 11, _internationalDesignatorYear.length(), _line1);
	putInLine(_internationalDesignator, 11, 14, _internationalDesignator.length(), _line1);
	putInLine(_piece, 14, 17, _piece.length(), _line1);
	putInLine(_epochYear, 18, 20, _epochYear.length(), _line1);
	putInLine(_epochTime, 20, 32, _epochTime.length(), _line1);
	putInLine(_meanMotionDerivative, 33, 43, _meanMotionDerivative.length(), _line1);
	putInLine(_meanMotionSecondDerivative, 44, 52, _meanMotionSecondDerivative.length(), _line1);
	putInLine(_averageAcceleration, 53, 61, _averageAcceleration.length(), _line1);
	putInLine(_typeOfEphemeris, 62, 63, _typeOfEphemeris.length(), _line1);
	putInLine(_elementsNumber, 64, 68, _elementsNumber.length(), _line1);
	putInLine(_chkSum, 68, 69, _chkSum.length(), _line1);
	string _line2 = "                                                                     ";
	putInLine(_numberOfLine2, 0, 1, _numberOfLine2.length(), _line2);
	putInLine(_satelliteNumbers2, 2, 7, _satelliteNumbers2.length(), _line2);
	putInLine(_inclination, 8, 16, _inclination.length(), _line2);
	putInLine(_rightAscensionOfTheNode, 17, 25, _rightAscensionOfTheNode.length(), _line2);
	putInLine(_eccentricity, 26, 33, _eccentricity.length(), _line2);
	putInLine(_argOfPerigee, 34, 42, _argOfPerigee.length(), _line2);
	putInLine(_meanAnomaly, 43, 51, _meanAnomaly.length(), _line2);
	putInLine(_meanMotion, 52, 63, _meanMotion.length(), _line2);
	putInLine(_epochRev, 63, 68, _epochRev.length(), _line2);
	putInLine(_chk, 68, 69, _chk.length(), _line2);
	string ret = "TLE (" + to_string(id) + ")\r\n";
	ret += _line1 + "\r\n";
	ret += _line2 + "\r\n";
	return ret;
}
string TLE::getLine1() {
	string _line1 = "                                                                     ";
	putInLine(_numberOfLine1, 0, 1, _numberOfLine1.length(), _line1);
	putInLine(_satelliteNumbers1, 2, 7, _satelliteNumbers1.length(), _line1);
	putInLine(_classification, 7, 8, _classification.length(), _line1);
	putInLine(_internationalDesignatorYear, 9, 11, _internationalDesignatorYear.length(), _line1);
	putInLine(_internationalDesignator, 11, 14, _internationalDesignator.length(), _line1);
	putInLine(_piece, 14, 17, _piece.length(), _line1);
	putInLine(_epochYear, 18, 20, _epochYear.length(), _line1);
	putInLine(_epochTime, 20, 32, _epochTime.length(), _line1);
	putInLine(_meanMotionDerivative, 33, 43, _meanMotionDerivative.length(), _line1);
	putInLine(_meanMotionSecondDerivative, 44, 52, _meanMotionSecondDerivative.length(), _line1);
	putInLine(_averageAcceleration, 53, 61, _averageAcceleration.length(), _line1);
	putInLine(_typeOfEphemeris, 62, 63, _typeOfEphemeris.length(), _line1);
	putInLine(_elementsNumber, 64, 68, _elementsNumber.length(), _line1);
	putInLine(_chkSum, 68, 69, _chkSum.length(), _line1);
	return _line1;
}
string TLE::getLine2() {
	string _line2 = "                                                                     ";
	putInLine(_numberOfLine2, 0, 1, _numberOfLine2.length(), _line2);
	putInLine(_satelliteNumbers2, 2, 7, _satelliteNumbers2.length(), _line2);
	putInLine(_inclination, 8, 16, _inclination.length(), _line2);
	putInLine(_rightAscensionOfTheNode, 17, 25, _rightAscensionOfTheNode.length(), _line2);
	putInLine(_eccentricity, 26, 33, _eccentricity.length(), _line2);
	putInLine(_argOfPerigee, 34, 42, _argOfPerigee.length(), _line2);
	putInLine(_meanAnomaly, 43, 51, _meanAnomaly.length(), _line2);
	putInLine(_meanMotion, 52, 63, _meanMotion.length(), _line2);
	putInLine(_epochRev, 63, 68, _epochRev.length(), _line2);
	putInLine(_chk, 68, 69, _chk.length(), _line2);
	return _line2;
}


void putInLine(std::string ch, int from, int to, int size, string& _line) {
	int j = 0;
	for (int i = from + (to - from - size); i < to; i++, j++) {
		_line[i] = ch[j];
	}
}
