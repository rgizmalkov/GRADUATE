#include <string>
#include "integration.h"
#include "OrbVec.h"
#include <math.h>
#include "func.h"
#include <iostream>
#include <ctime>
#include "calculation.h"
#include "add_func.h"
#pragma warning (disable : 4996)

std::string calculation(OrbVec catSC, OrbVec ourSC, double interval, double step, std::string name) {
	// siece 1970 time
	double timeCatSC = catSC.getTime();//jd
	double timeOurSC = ourSC.getTime();//jd!
	double realTime;

	double rCat[3], vCat[3], rOur[3], vOur[3];
	catSC.getR(rCat);
	catSC.getV(vCat);
	ourSC.getR(rOur);
	ourSC.getV(vOur);

	double dif = timeOurSC - timeCatSC;
	while (true){
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
		if (-3/86400. <= dif && dif <= 3 / 86400.) break;
	}

	// now timeCatSC == timeOurSC -> TRUE 100%
	double maxDist = 9999999999;
	FILE *fset = fopen(name.c_str(), "ab");
	std::string str = "";
	str += "Tested SC: " + ourSC.getName() + " | Catalog SC: " + catSC.getName() + "\n";


	double colTime = iteracii2(rCat, vCat, rOur, vOur, interval, step, realTime, maxDist, fset);
	if (colTime != 0) {
		str += status(catSC, ourSC, rCat, vCat, rOur, vOur, colTime, maxDist);
		fwrite(str.c_str(), str.length(), 1, fset);
	}
	else {
		str += "start = " + std::to_string(ourSC.getTime()) + " | end = " + std::to_string(realTime);
		str += "\n--------------------------------------------------------------------------------\n";
		fwrite(str.c_str(), str.length(), 1, fset);
	}
	fclose(fset);
	return "";
}
std::string calculationTime(OrbVec catSC, OrbVec ourSC, double interval, double step, std::string name) {
	// siece 1970 time
	unsigned int start_time = clock();

	double timeCatSC = catSC.getTime();//jd
	double timeOurSC = ourSC.getTime();//jd!
	double realTime;

	double rCat[3], vCat[3], rOur[3], vOur[3];
	catSC.getR(rCat);
	catSC.getV(vCat);
	ourSC.getR(rOur);
	ourSC.getV(vOur);

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
	FILE *fset = fopen(name.c_str(), "ab");
	std::string str = "";
	str += "Tested SC: " + ourSC.getName() + " | Catalog SC: " + catSC.getName() + "\n";


	double colTime = iteracii2(rCat, vCat, rOur, vOur, interval, step, realTime, maxDist, fset);
	unsigned int end_time = clock();
	std::string strTime = ourSC.getName() + "|" + catSC.getName() + "|" + std::to_string(end_time - start_time) + "\n";
	if (colTime != 0) {
		str += status(catSC, ourSC, rCat, vCat, rOur, vOur, colTime, maxDist);
		fwrite(str.c_str(), str.length(), 1, fset);
	}
	else {
		str += "start = " + std::to_string(ourSC.getTime()) + " | end = " + std::to_string(realTime);
		str += "\n--------------------------------------------------------------------------------\n";
		fwrite(str.c_str(), str.length(), 1, fset);
	}
	fclose(fset);

	return strTime;
}
std::string format(int hour1, int min1, int sec1) {
	std::string str = "";
	std::string hour = std::to_string(hour1);
	std::string min = std::to_string(min1);
	std::string sec = std::to_string(sec1);
	if (hour.length() != 2) {
		hour = "0" + hour;
	}
	if (min.length() != 2) {
		min = "0" + min;
	}
	if (sec.length() != 2) {
		sec = "0" + sec;
	}
	str = hour + ":" + min + ":" + sec;
	return str;
}
std::string formatDate(int year1, int month1, int day1) {
	std::string str = "";
	std::string year = std::to_string(year1);
	std::string month = std::to_string(month1);
	std::string day = std::to_string(day1);
	if (month.length() != 2) {
		month = "0" + month;
	}
	if (day.length() != 2) {
		day = "0" + day;
	}
	str = day + "/" + month + "/" + year;
	return str;
}
void JulDateToDateTime2(double JD, int &Year, int &Month, int &Day, int &Hour, int &Min, double &Sec) {
	if (JD <= 0)
	{
		Year = 0;
		Month = 0;
		Day = 0;
		Hour = 0;
		Min = 0;
		Sec = 0;
	}
	else
	{
		long a, b, c, d, e, f;
		double FracOfDay;
		//Преобразуем номер юлианского дня в календарную дату
		a = (long)(JD + 0.5);
		if (a<2299161) {
			b = 0;
			c = a + 1524;
		}
		else {
			b = (long)((a - 1867216.25) / 36524.25);
			c = a + b - (b / 4) + 1525;
		}
		d = (long)((c - 122.1) / 365.25);
		e = 365 * d + d / 4;
		f = (long)((c - e) / 30.6001);
		Day = c - e - (int)(30.6001*f);
		Month = f - 1 - 12 * (f / 14);
		Year = d - 4715 - ((7 + Month) / 10);
		FracOfDay = (JD - 0.5 - (int)(JD - 0.5))*24.0;//вещественное количество часов
		Hour = (int)(FracOfDay);				  //целое количество часов
		FracOfDay = (FracOfDay - Hour)*60.0;	  //вещественное количество минут	
		Min = (int)(FracOfDay);				  //целое количество минут
		Sec = (FracOfDay - Min)*60.0;			  //вещественное количество секунд
	}
}
void to_vec_6(double vect_next[], double r1[], double v1[]) {
	for (int i = 0; i < 3; i++) {
		vect_next[i] = r1[i];
		vect_next[i+3] = v1[i];
	}
}
std::string status(OrbVec cat, OrbVec test, double r1[3], double v1[3], double r2[3], double v2[3], double colTime, double distance) {
	double rCat[3], vCat[3], rOur[3], vOur[3];
	cat.getR(rCat);
	cat.getV(vCat);
	test.getR(rOur);
	test.getV(vOur);
	double a; double e; double i; double Q; double w; double teta;
	double a2; double e2; double i2; double Q2; double w2; double teta2;
	double da;double de;double di;
	double da2;double de2;double di2;

	double vect_next[6];
	double vect_nextTest[6];

	to_vec_6(vect_next, r1, v1);
	to_vec_6(vect_nextTest, r2, v2);
	CoordsToElements(vect_next, a, e, i, Q, w, teta);
	CoordsToElements(vect_nextTest, a2, e2, i2, Q2, w2, teta2);

	std::string str = "#-#-#-COLLISION-#-#-#\n";
	str += "Catalog Satellite is:\n";
	str += "R: " + std::to_string(vect_next[0]) + "	  " + std::to_string(vect_next[1]) + "	  " + std::to_string(vect_next[2]) + "\n";
	str += "V: " + std::to_string(vect_next[3]) + "		" + std::to_string(vect_next[4]) + "		" + std::to_string(vect_next[5]) + "\n";
	str += "Kep. elements: \n";
	str += std::to_string(a) + " " + std::to_string(e) + " " + std::to_string(i) + "\n";
	str += std::to_string(Q) + " " + std::to_string(w) + " " + std::to_string(teta) + "\n";
	str += "Testing Satellite is:\n";
	str += "R: " + std::to_string(vect_nextTest[0]) + "   " + std::to_string(vect_nextTest[1]) + "   " + std::to_string(vect_nextTest[2]) + "\n";
	str += "V: " + std::to_string(vect_nextTest[3]) + "		" + std::to_string(vect_nextTest[4]) + "		" + std::to_string(vect_nextTest[5]) + "\n";
	str += "Kep. elements: \n";
	str += std::to_string(a2) + " " + std::to_string(e2) + " " + std::to_string(i2) + "\n";
	str += std::to_string(Q2) + " " + std::to_string(w2) + " " + std::to_string(teta2) + "\n";
	str += "Julian Date: " + std::to_string(colTime) + "\n";
	str += "distance is: " + std::to_string(distance) + "\n\n";

	to_vec_6(vect_next, r1, v1);
	to_vec_6(vect_nextTest, rCat, vCat);
	CoordsToElements(vect_next, a, e, i, Q, w, teta);
	CoordsToElements(vect_nextTest, a2, e2, i2, Q2, w2, teta2);
	int year;int month;int day;int hour;int min; double sec;
	JulDateToDateTime2(cat.getTime(), year, month, day, hour, min, sec);
	str += "\nStatus:\n";
	str += "CS JD: " + std::to_string(cat.getTime()) + " ---Caledar Time---> " + formatDate(year,month,day) + " " + format(hour,day,sec) + "\n";
	da = a2 - a; de = e2 - e; di = i2 - i;
	str += "?a = " + std::to_string(da) + " ?e = " + std::to_string(de) + " ?i = " + std::to_string(di) + "\n";
	JulDateToDateTime2(test.getTime(), year, month, day, hour, min, sec);
	to_vec_6(vect_next, r2, v2);
	to_vec_6(vect_nextTest, rOur, vOur);
	CoordsToElements(vect_next, a, e, i, Q, w, teta);
	CoordsToElements(vect_nextTest, a2, e2, i2, Q2, w2, teta2);
	da2 = a2 - a; de2 = e2 - e; di2 = i2 - i;
	str += "TS JD: " + std::to_string(test.getTime()) + " ---Caledar Time---> " + formatDate(year, month, day) + " " + format(hour, day, sec) + "\n";
	str += "?a = " + std::to_string(da2) + " ?e = " + std::to_string(de2) + " ?i = " + std::to_string(di2) + "\n";
	JulDateToDateTime2(colTime, year, month, day, hour, min, sec);
	str += "Collision time:                           " + formatDate(year, month, day) + " " + format(hour, day, sec) + "\n";
	str += "\n--------------------------------------------------------------------------------\n";

	return str;
}

std::string timeAnalize(OrbVec catSC, double interval, double step, FILE *fset) {
	
	double rCat[3], vCat[3];
	double timeCatSC = catSC.getTime();
	catSC.getR(rCat);
	catSC.getV(vCat);
	unsigned int start_time = clock();
	iteraciiTestTime(rCat, vCat, interval, step, timeCatSC);
	unsigned int end_time = clock();
	std::string str = std::to_string(end_time - start_time);
	return str;
}



//int main21(void) {
//	double x = 7169.763191;
//	double y = -639.865448;
//	double z = -11.173054;
//	double xV = -0.093532;
//	double yV = 1.161903;
//	double zV = 7.349254;
//	double t = 2457427.692486;
//
//	OrbVec catSc = OrbVec(x , y, z, xV, yV, zV, JulianDateToDateTime(t));
//
//	double x1 = 1463.073761;
//	double y1 = 3507.113444;
//	double z1 = 6165.438235;
//	double xV1 = -0.318827;
//	double yV1 = -6.410347;
//	double zV1 = 3.684963;
//	double t1 = 2457425.831922;
//	OrbVec ourSc = OrbVec(x1, y1, z1, xV1, yV1, zV1, JulianDateToDateTime(t1));
//
//	calculation(catSc, ourSc, 90*86400., 1);
//	return 0;
//}
