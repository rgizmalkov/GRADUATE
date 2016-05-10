#include <ctime>
#include <math.h>
#include "func.h"
#include "constants.h"
#include <string>
#include "add_func.h"
#include "TLE.h"
#include <cmath>
#pragma warning (disable : 4996)


void write(double vect_next[6], double vect_nextTest[6], double distance, double date, FILE *file) {
	double a; double e; double i; double Q; double w; double teta;
	double a2; double e2; double i2; double Q2; double w2; double teta2;

	CoordsToElements(vect_next, a, e, i, Q, w, teta);
	CoordsToElements(vect_nextTest, a2, e2, i2, Q2, w2, teta2);

	int count = 0;
	std::string str = "\\\-\\\-\\\-COLLISION-//-//-//\n";
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
	str += "Julian Date: " + std::to_string(date) + "\n";
	str += "distance is: " + std::to_string(distance) + "\n\n";
	
	char const *chString = str.c_str();
	count = fwrite(chString, strlen(chString), 1, file);
	//printf("Записано %lu байт. fclose(fp) %s.\n", (unsigned long)count, fclose(file) == 0 ? "успешно" : "с ошибкой");
}

// Перевод Юлианского дня в Звезное время
double GMST(double dat) {
	double st, JD, JD0, Tut, n;
	//JD = UTtoJD(dat);
	//JD = DateTimeToJulianDate(long(dat));
	JD = dat;
	modf(JD - 0.5, &n);
	JD0 = n + 0.5;
	Tut = (JD0 - 2451545) / 36525;
	st = 1.7533685592 + 628.3319706889*Tut + 6.7707139e-6*Tut*Tut
		- 4.50876*10.0e-10*Tut*Tut*Tut + 1.002737909350795 * 2 * M_PI*(JD - JD0);
	modf(st / (2 * M_PI), &n);
	return st - n * 2 * M_PI; // в приведённых радианах
}
double ModulVec(double x, double y, double z) {
	return sqrt(x*x + y*y + z*z);
}
//---------------------------------------------------------------------------
// Расчет модуля вектора
double DateTimeToJulianDate(time_t time) {
	tm* t = localtime(&time);
	int year = t->tm_year + 1900;
	//-----> number of seconds sience 1970
	//int year = 1970 + int(time / 31557600);
	int A = int(year / 100);
	int B = 2 - A + int(A / 4);
	int M = t->tm_mon + 1;
	if (M <= 2) {
		year = year - 1;
		M = M + 12;
	}
	double JD = int(365.25 * (year + 4716)) + int(30.6001 * (M + 1)) + t->tm_mday + B - 1524.5;
	return JD;
}
double JulianDateToDateTime2(double jd) {
	int A;
	int Z = int(jd + 0.5);
	double F;
	if (jd >= Z) {
		F = jd - Z;
	}
	else {
		F = Z - jd;
	}
	if (Z < 2299161) {
		A = Z;
	}
	else {
		int alpha11 = int((Z - 1867216.25) / 36524.25);
		A = Z + 1 + alpha11 - int(alpha11 / 4);
	}
	int B = A + 1524;
	int C = int((B - 122.1) / 365.25);
	int D = int(365.25*C);
	int E = int((B - D) / 30.6001);
	double day = B - D - int(30.6001 * E) + F;
	int month;
	if (E < 14) month = E - 1;
	else month = E - 13;
	int year;
	if (month > 2) year = C - 4716;
	else year = C - 4715;
	double date = ((year - 1970)*365.25 + (month*30.6001) + day) * 86400;
	return date;
}
double JulianDateToDateTime(double JD) {
	double Year = 0;
	double Month = 0;
	double Day = 0;
	double Hour = 0;
	double Min = 0;
	double Sec = 0;
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
		//if(f < 14) Month = f - 1 - 12 * (f / 14);
		Month = f - 1 - 12 * (f / 14);
		if (Month > 2) Year = d - 4716 - ((7 + Month) / 10);
		else
		{
			Year = d - 4715 - ((7 + Month) / 10);
		}
		FracOfDay = (JD - 0.5 - (int)(JD - 0.5))*24.0;//вещественное количество часов
		Hour = (int)(FracOfDay);				  //целое количество часов
		FracOfDay = (FracOfDay - Hour)*60.0;	  //вещественное количество минут	
		Min = (int)(FracOfDay);				  //целое количество минут
		Sec = (FracOfDay - Min)*60.0;			  //вещественное количество секунд
		double date = ((Year - 1970)* 365.25 + Month*(30.60001) + Day)* 86400. + Hour * 3600 + Min * 60 + Sec;
		return date;
}

double ModulVec(double x[3]) {
	return sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
}
//double DateTimeToJulianDate(double date)
//{
//	return (date / 86400.) + 2415018.5;
//}
//
//double WrapDateTimeToJulianDate(double dt) {
//	if ((dt - (int)dt)>0.999999994) dt = (int)dt + 1;
//	return DateTimeToJulianDate(dt);
//}
void WGS84toGEI3(const double Ar1[3], const double t, double Ar2[3]) {
	double cs, ss, s,
		S[3][3], NP[3][3],
		PNS[3][3], dob;

	precessionVSnutation(t, s, NP);
	cs = cos(s);
	ss = sin(s);
	S[0][0] = cs;		S[0][1] = -ss; 	S[0][2] = 0;
	S[1][0] = ss;		S[1][1] = cs; 	S[1][2] = 0;
	S[2][0] = 0;		S[2][1] = 0; 	 	S[2][2] = 1;
	for (int c = 0; c<3; c++)
		for (int i = 0; i<3; i++) {
			PNS[i][c] = 0;
			for (int j = 0; j<3; j++) PNS[i][c] += NP[j][i] * S[j][c];
		}
	for (int i = 0; i<3; i++) {
		Ar2[i] = 0;
		for (int j = 0; j<3; j++) Ar2[i] += PNS[i][j] * Ar1[j];
	}
}
//Преобразование Второй Экваториальной в Гринвическую (ТОЛЬКО ПОЛОЖЕНИЕ)
void GEI3toWGS84(const double Ar1[3], const double t, double Ar2[3]) {
	double cs, ss, s,
		S[3][3], NP[3][3],
		SNP[3][3], dob;

	precessionVSnutation(t, s, NP);
	cs = cos(s);
	ss = sin(s);
	S[0][0] = cs;		S[0][1] = ss; 	S[0][2] = 0;
	S[1][0] = -ss;	S[1][1] = cs; 	S[1][2] = 0;
	S[2][0] = 0;		S[2][1] = 0; 	 	S[2][2] = 1;
	for (int c = 0; c<3; c++)
		for (int i = 0; i<3; i++) {
			SNP[i][c] = 0;
			for (int j = 0; j<3; j++) SNP[i][c] += S[i][j] * NP[j][c];
		}
	for (int i = 0; i<3; i++) {
		Ar2[i] = 0;
		for (int j = 0; j<3; j++) Ar2[i] += SNP[i][j] * Ar1[j];
	}
}
//---------------------------------------------------------------------------
void precessionVSnutation(const double t, double &s, double NP[3][3]) {
	double ksi, zeta, teta, psi, eps, eps0;
	double 	c_ksi, s_ksi,
		c_zeta, s_zeta,
		c_teta, s_teta,
		c_psi, s_psi,
		c_eps, s_eps,
		c_eps0, s_eps0;
	double T, T2, T3;
	double Ml, Ms, ul, Ds, Uzl;
	double P[3][3], N[3][3];
	T = (UTCtoTDB(t) - 2451545.0) / 36525.0;
	T2 = T*T;
	T3 = T2*T;
	ksi = 0.011180860*T + 1.464E-6*T2 + 8.70E-8*T3;
	zeta = 0.011180860*T + 5.308E-6*T2 + 8.90E-8*T3;
	teta = 0.009717173*T - 2.068E-6*T2 - 2.02E-7*T3;
	eps0 = 0.4090928042 - 0.2269655E-3*T - 2.86E-9*T2 + 8.80E-9*T3;

	Ml = 2.355548394 + (1325 * 2 * M_PI + 3.470890873)*T + 1.517952E-4*T2 + 3.103E-7*T3;
	Ms = 6.240035940 + (99 * 2 * M_PI + 6.266610600)*T - 2.797400E-6*T2 - 5.820E-8*T3;
	ul = 1.627901934 + (1342 * 2 * M_PI + 1.431476084)*T - 6.427170E-5*T2 + 5.340E-8*T3;
	Ds = 5.198469514 + (1236 * 2 * M_PI + 5.360106500)*T - 3.340860E-5*T2 + 9.220E-8*T3;
	Uzl = 2.182438624 - (5 * 2 * M_PI + 2.341119397)*T + 3.614290E-5*T2 + 3.880E-8*T3;

	eps = 0; psi = 0;
	for (int i = 0;i <= 105;i++) {
		psi += (coef_A[i] + coef_B[i] * T)*sin(coef_a1[i] * Ml + coef_a2[i] * Ms + coef_a3[i] * ul + coef_a4[i] * Ds + coef_a5[i] * Uzl);
		eps += (coef_C[i] + coef_D[i] * T)*cos(coef_a1[i] * Ml + coef_a2[i] * Ms + coef_a3[i] * ul + coef_a4[i] * Ds + coef_a5[i] * Uzl);
	}
	psi = psi*1E-4 / 3600. / 180.*M_PI;
	eps = eps*1E-4 / 3600. / 180.*M_PI;
	eps += eps0;

	//if (need_psi) *need_psi = psi;//для МЕТЕ

	c_ksi = cos(ksi);
	s_ksi = sin(ksi);
	c_zeta = cos(zeta);
	s_zeta = sin(zeta);
	c_teta = cos(teta);
	s_teta = sin(teta);
	c_psi = cos(psi);
	s_psi = sin(psi);
	c_eps = cos(eps);
	s_eps = sin(eps);
	c_eps0 = cos(eps0);
	s_eps0 = sin(eps0);

	//if (need_c_eps) *need_c_eps = c_eps;//для МЕТЕ

										//истинное звездное время TRUE_GMST
	s = GMST(t) + psi*c_eps;

	P[0][0] = c_ksi*c_zeta*c_teta - s_ksi*s_zeta;
	P[0][1] = -s_ksi*c_zeta*c_teta - c_ksi*s_zeta;
	P[0][2] = -c_zeta*s_teta;

	P[1][0] = c_ksi*s_zeta*c_teta + s_ksi*c_zeta;
	P[1][1] = -s_ksi*s_zeta*c_teta + c_ksi*c_zeta;
	P[1][2] = -s_zeta*s_teta;

	P[2][0] = c_ksi*s_teta;
	P[2][1] = -s_ksi*s_teta;
	P[2][2] = c_teta;

	N[0][0] = c_psi;
	N[0][1] = -s_psi*c_eps0;
	N[0][2] = -s_psi*s_eps0;

	N[1][0] = s_psi*c_eps;
	N[1][1] = c_psi*c_eps*c_eps0 + s_eps*s_eps0;
	N[1][2] = c_psi*c_eps*s_eps0 - s_eps*c_eps0;

	N[2][0] = s_psi*s_eps;
	N[2][1] = c_psi*s_eps*c_eps0 - c_eps*s_eps0;
	N[2][2] = c_psi*s_eps*s_eps0 + c_eps*c_eps0;

	for (int c = 0; c<3; c++)
		for (int i = 0; i<3; i++) {
			NP[i][c] = 0;
			for (int j = 0; j<3; j++)
				NP[i][c] += N[i][j] * P[j][c];
		}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//перевод UTC в TDB
//TDateTime UTCtoTDB(TDateTime dat) { return dat + 67.184 / 86400; }
double UTCtoTDB(double JD) { return JD + 67.184 / 86400; }
//Преобразование Гринвической во Вторую Экваториальную


// calculating defference between coordinates 
double distanceCollision(double r[3], double r2[3]) {
	double xab = r[0] - r2[0];
	double yab = r[1] - r2[1];
	double zab = r[2] - r2[2];

	double xab2 = xab * xab;
	double yab2 = yab * yab;
	double zab2 = zab * zab;

	double sum = xab2 + yab2 + zab2;
	
	double ab = sqrt(sum);

	return ab;
}

bool screening(TLE sat1, TLE sat2, std::vector<double> &R1, std::vector<double> &R2) {
	// Запросом отбирали орбиты по критерию 1.
	/*Ex.
	std::string query = "select * from orbitcomponents o, (select * from orbitcomponents where id = " + testSC + ") iss where  not(iss.a*(1 + iss.e) < o.a*(1 - o.e)) and not(iss.a*(1 + o.e) < o.a*(1 - iss.e)) and not(o.id = " + testSC + ");";
	std::string query1 = "select * from orbitcomponents where id =" + testSC; //	LUCH 5B
	*/

	// Расчитываем радиус вектора, через сечение шара.
	const double eps = 10;

	double omega1 = sat1.getW();
	double omega2 = sat2.getW();

	double incl1 = sat1.getI();
	double incl2 = sat2.getI();

	double cosi12 = -cos(incl1)*cos(incl2) + sin(incl1)*sin(incl2)*cos(abs(omega1 - omega2));

	if (cosi12 < eps) return false;

	double sin_i2i12 = sin(incl1)*sin(acos(cosi12)) / sin(incl2);
	double sin_i1i12 = sin(incl1)*sin(incl2) / sin(acos(cosi12));

	double cos_u1 = cos(asin(sin_i1i12)) - cos(1)*cos(1) / sin(1)* sin(1);
	double cos_u1 = cos(asin(sin_i2i12)) - cos(1)*cos(1) / sin(1)* sin(1);


}