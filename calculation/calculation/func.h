#pragma once
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double ModulVec(double x[3]);
double ModulVec(double x, double y, double z);
double WrapDateTimeToJulianDate(double dt);
void WGS84toGEI3(const double Ar1[3], const double t, double Ar2[3]);
void GEI3toWGS84(const double Ar1[3], const double t, double Ar2[3]);
double JulianDateToDateTime(double jd);
double DateTimeToJulianDate(time_t time);
double GMST(double dat);
double UTCtoTDB(double JD);
void precessionVSnutation(const double t, double &s, double NP[3][3]);
double distanceCollision(double r[3], double r2[3]);
void write(double sc[6], double sc2[6], double distance, double date, FILE *file);