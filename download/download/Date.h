#pragma once
#include <time.h>
#include <string>
#pragma warning(disable : 4996)
using namespace std;
class Date
{
private:
	struct tm  mtime = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
	string stime;
	void setDate(char, string&);
	string getDate(char);
public:
	Date();
	Date(tm);
	Date(string&, string);
	static Date* newInstance();
	~Date();
	long operator-(Date date);
	//vars
	static const string DB_FORMAT;
	static const string DATE;
	static const string TIME;
	//methods
	double dateTimeToJulianDate();
	//setters
	void setTime(tm val) { this->mtime = val; }
	void setSTime(string val) { this->stime = val; }
	//getters
	tm getTime() { return this->mtime; }
	string getSTime(){ return this->stime; }
	string getFTime(string);
};

