#include "OrbVec.h"
#include <string>


OrbVec::OrbVec(double x, double y, double z, double xV, double yV, double zV, double time, std::string name)
{
	setX(x);
	setY(y);
	setZ(z);
	setXV(xV);
	setYV(yV);
	setZV(zV);
	setTime(time);
	setName(name);
}


OrbVec::~OrbVec()
{
}
