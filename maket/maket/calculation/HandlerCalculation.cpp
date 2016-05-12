#include "HandlerCalculation.h"
#include "..\sgp4v\constants.h"
#include "integration.h"
const string HandlerCalculation::FIRST_SELECTION_1 = "select * from sat, (select (k1.id) from kep k1, (select * from kep where id = ";
const string HandlerCalculation::FIRST_SELECTION_2 = ") k2 where not(k2.a*(1+k2.e) < k1.a*(1 - k1.e)) and not(k1.a*(1+k1.e) < k2.a*(1 - k2.e)) and not(k1.id = ";
const string HandlerCalculation::FIRST_SELECTION_3 = ")) sel where sat.id = sel.id;";



HandlerCalculation::HandlerCalculation(Satellite* sat)
{
	sql = MySQL::newInstanse();
	this->sat = sat;
	firstSelection();
	secondSelectionR();
	secondSelectionL();
}


HandlerCalculation::~HandlerCalculation()
{
}

void HandlerCalculation::firstSelection() {
	int id = sat->getId();
	string query = FIRST_SELECTION_1 + to_string(id) + FIRST_SELECTION_2 + to_string(id) + FIRST_SELECTION_3;
	MYSQL_RES * result = sql->execute(query);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)) != NULL) {
		Satellite * sat = new Satellite();
		sat->loadEntity(row);
		selected.push_back(sat);
	}
};

void HandlerCalculation::secondSelectionR() {
	// Compare 
	vector<Satellite*> newVec;
	const double eps = 0.1;
	const double reps = 200;


	double omega1 = this->sat->getKep()->getO();
	double omega2;
	double incl1 = this->sat->getKep()->getI();
	double incl2;
	double e1 = this->sat->getKep()->getE();
	double e2;
	double w1 = this->sat->getKep()->getW();
	double w2;
	double a1 = this->sat->getKep()->getA();
	double a2;

	for (int i = 0; i < selected.size(); i++) {
		omega2 = selected[i]->getKep()->getO();
		incl2 = M_PI - selected[i]->getKep()->getI();
		e2 = selected[i]->getKep()->getE();
		w2 = selected[i]->getKep()->getW();
		a2 = selected[i]->getKep()->getA();

		double cosi12 = -cos(incl1)*cos(incl2) + sin(incl1)*sin(incl2)*cos(abs(omega1 - omega2));
		if (cosi12 < eps) {
			newVec.push_back(selected[i]);
			continue;
		}
		double u1 = sin(incl1)*sin(acos(cosi12)) / sin(incl2);
		double u2 = sin(incl1)*sin(incl2) / sin(acos(cosi12));

		double v1 = u1 + w1;
		double R1 = (a1*(1 - e1*e1)) / (1 + e1*cos(v1));
		double v2 = u2 + w2;
		double R2 = (a2*(1 - e2*e2)) / (1 + e2*cos(v2));

		double mod = abs(R2 - R1);
		if (mod < reps) {
			newVec.push_back(selected[i]);
			continue;
		}
	}
	selected = newVec;
};
void HandlerCalculation::secondSelectionL() {
	// Compare 
	vector<Satellite*> newVec;
	const double eps = 0.1;
	const double reps = 200;


	double omega1 = this->sat->getKep()->getO();
	double omega2;
	double incl1 = M_PI - this->sat->getKep()->getI();
	double incl2;
	double e1 = this->sat->getKep()->getE();
	double e2;
	double w1 = this->sat->getKep()->getW();
	double w2;
	double a1 = this->sat->getKep()->getA();
	double a2;

	for (int i = 0; i < selected.size(); i++) {
		omega2 = selected[i]->getKep()->getO();
		incl2 = M_PI - selected[i]->getKep()->getI();
		e2 = selected[i]->getKep()->getE();
		w2 = selected[i]->getKep()->getW();
		a2 = selected[i]->getKep()->getA();

		double cosi12 = -cos(incl1)*cos(incl2) + sin(incl1)*sin(incl2)*cos(abs(omega1 - omega2));
		if (cosi12 < eps) {
			newVec.push_back(selected[i]);
			continue;
		}
		double u1 = sin(incl1)*sin(acos(cosi12)) / sin(incl2);
		double u2 = sin(incl1)*sin(incl2) / sin(acos(cosi12));

		double v1 = u1 + w1;
		double R1 = (a1*(1 - e1*e1)) / (1 + e1*cos(v1));
		double v2 = u2 + w2;
		double R2 = (a2*(1 - e2*e2)) / (1 + e2*cos(v2));

		double mod = abs(R2 - R1);
		if (mod < reps) {
			newVec.push_back(selected[i]);
			continue;
		}
	}
	selected = newVec;
};
void HandlerCalculation::calculation(State state, double interval, double step) {
	// siece 1970 time
	double timeOurSC = this->sat->getState()->getJD();//jd!
	double timeCatSC = state.getJD();//jd
	double realTime;

	double rCat[3], vCat[3], rOur[3], vOur[3];
	sat->getState()->getR(rOur);
	sat->getState()->getV(vOur);
	state.getR(rCat);
	state.getV(vCat);
	

	double dif = timeOurSC - timeCatSC;
	while (true) {
		if (dif > 0) {
			iteracii(rCat, vCat, dif, step, timeCatSC);
			realTime = timeCatSC;
		}
		else if (dif < 0) {
			iteracii(rOur, vOur, fabs(dif), step, timeOurSC);
			realTime = timeOurSC;
		}
		else {
			realTime = timeOurSC;
		}
		dif = timeOurSC - timeCatSC;
		if (-3 / 86400. <= dif && dif <= 3 / 86400.) break;
	}

	// now timeCatSC == timeOurSC -> TRUE 100%
	double maxDist = 9999999999;
	vector<string> col;
	std::string str = "";
	str += "Tested SC: " + to_string(sat->getState()->getId()) + " | Catalog SC: " + to_string(state.getId()) + "\n";
	fw.write(str);
	double colTime = iteracii2(rCat, vCat, rOur, vOur, interval, step, realTime, maxDist, col);
	for (int i = 0; i < col.size(); i++) fw.write(col[i]);
	str = "start = " + std::to_string(sat->getState()->getJD()) + " | end = " + std::to_string(realTime);
	str += "\n--------------------------------------------------------------------------------\n";
	fw.write(str);
}

void HandlerCalculation::calculat(double interval, double step, string filename) {
	fw.setFile(filename);
	for (int i = 0; i < selected.size(); i++) {
		calculation(*(selected[i]->getState()), interval, step);
	}
	fw.close();
};