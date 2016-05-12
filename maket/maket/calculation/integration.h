#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;
void iteracii(double r_0[3], double V_0[3], double interval, double dt, double &t_0);
double iteracii2(double r_0[3], double V_0[3], double r_02[3], double V_02[3], double interval, double dt, double &t_0, double &maxDist, vector<string> &col);
void iteraciiTestTime(double r_0[3], double V_0[3], double interval, double dt, double &t_0);
void iteraciiGetCoord(double r_0[3], double V_0[3], double interval, double dt, double &t_0);