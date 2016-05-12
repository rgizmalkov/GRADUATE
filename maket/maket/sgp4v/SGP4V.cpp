// SGP4V.cpp: определяет точку входа для консольного приложения.
//

#include "SGP4V.h"


double* jsgp4v(std::string jstr1, std::string jstr2, double* outRV){
//std::string jstr1 = "1 25544U 98067A   08264.51782528 -.00002182  00000-0 -11606-4 0  2927";
//std::string jstr2 = "2 25544  51.6416 247.4627 0006703 130.5360 325.0288 15.72125391563537";
const char *line1 = jstr1.c_str();
const char *line2 = jstr2.c_str();
char str[2];
char infilename[15];
double ro[3];
double vo[3];
char typerun, typeinput, opsmode;
gravconsttype whichconst;
int whichcon;
Vector<> R_teme, V_teme,
		 R_J2000,V_J2000;
Matrix<> GSK_TEME_M, TEME_GSK_M;
// ---------------------------- locals -------------------------------
double p, a, ecc, incl, node, argp, nu, m, arglat, truelon, lonper;
double sec, jd, rad, tsince, startmfe, stopmfe, deltamin;
double tumin, mu, radiusearthkm, xke, j2, j3, j4, j3oj2;
int year; int mon; int day; int hr; int min;
char longstr1[130];
typedef char str3[4];
str3 monstr[13];
char outname[64];
char longstr2[130];
elsetrec satrec;
rad = 180.0 / pi;
double date;	
whichconst = wgs84;
getgravconst(whichconst, tumin, mu, radiusearthkm, xke, j2, j3, j4, j3oj2);

strcpy_s(longstr1, line1);
strcpy_s(longstr2, line2);

startmfe = 0.0;
stopmfe = 1440.0;
deltamin = 10;
typerun = 'c';
typeinput = 'm';
opsmode = 'a';
twoline2rv(longstr1, longstr2, typerun, typeinput, opsmode, whichconst,
	startmfe, stopmfe, deltamin, satrec);

sgp4(whichconst, satrec, 0.0, ro, vo);
date = satrec.jdsatepoch;

//TEME_GSK(double(satrec.jdsatepoch), GSK_TEME_M, TEME_GSK_M);
TEME_GSK(date, GSK_TEME_M, TEME_GSK_M);

for (int i = 0;i<3;i++)
{
	R_teme[i] = ro[i];
	V_teme[i] = vo[i];
}
R_J2000 = TEME_GSK_M*R_teme;
V_J2000 = TEME_GSK_M*V_teme;


for (int i = 0; i < 3; i++) {
	outRV[i] = R_J2000[i];
}
for (int i = 3; i < 6; i++) {
	outRV[i] = V_J2000[i - 3];

}
//outRV[6] = ln_get_julian_from_timet(&date);
outRV[6] = date;
//ln_date JD;
//ln_get_date(date, &JD);
	//std::cout << outRV[0] << '\n';
	//std::cout << outRV[1] << '\n';
	//std::cout << outRV[2] << '\n';
	//std::cout << outRV[3] << '\n';
	//std::cout << outRV[4] << '\n';
	//std::cout << outRV[5] << '\n';
	//std::cout << JD.days << '/' << JD.months << '/' << JD.years << "     " << JD.hours << ':' << JD.minutes << ':' << JD.seconds << '\n' ;
	//system("pause");
    return outRV;
}


