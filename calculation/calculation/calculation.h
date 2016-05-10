#pragma once
#include <string>
#include "OrbVec.h"
std::string calculation(OrbVec catSC, OrbVec ourSC, double interval, double step, std::string name);
std::string timeAnalize(OrbVec catSC, double interval, double step, FILE *fset);
std::string status(OrbVec cat, OrbVec test, double r1[3], double v1[3], double r2[3], double v2[3], double colTime, double distance);