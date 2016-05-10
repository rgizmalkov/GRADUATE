#pragma once
#include <string>
class OrbVec
{
private:
	double x;
	double y;
	double z;

	double xV;
	double yV;
	double zV;
	// siece 1970 time
	double time;

	std::string name;
public:
	OrbVec(double x, double y, double z, double xV, double yV, double zV, double time, std::string name);
	~OrbVec();

	void setX(double xx) {
		x = xx;
	}
	void setY(double yy) {
		y = yy;
	}
	void setZ(double zz) {
		z = zz;
	}
	void setXV(double xx) {
		xV = xx;
	}
	void setYV(double yy) {
		yV = yy;
	}
	void setZV(double zz) {
		zV = zz;
	}
	void setTime(double time1) {
		time = time1;
	}
	void setName(std::string name1) {
		name = name1;
	}
	void getR(double r[3]) {
		r[0] = x;
		r[1] = y;
		r[2] = z;
	}
	void getV(double v[3]) {
		v[0] = xV;
		v[1] = yV;
		v[2] = zV;
	}
	double getTime() {
		return time;
	}
	std::string getName() {
		return name;
	}
};

