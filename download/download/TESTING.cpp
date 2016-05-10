#include <time.h>
#include <iostream>
#include <string>
#pragma warning (disable : 4996)
using namespace std;
double DateTimeToJulianDate(tm t) {
	int year = t.tm_year + 1900;
	//-----> number of seconds sience 1970
	//int year = 1970 + int(time / 31557600);
	int A = int(year / 100);
	int B = 2 - A + int(A / 4);
	int M = t.tm_mon + 1;
	if (M <= 2) {
		year = year - 1;
		M = M + 12;
	}
	double JD = int(365.25 * (year + 4716)) + int(30.6001 * (M + 1)) + t.tm_mday + B - 1524.5;
	cout << to_string(JD) << endl;
	JD += (double)t.tm_hour / (double)24 + (double)t.tm_min /(double) (24 * 60) + (double)t.tm_sec / (double)(24 * 3600);
	cout << to_string(JD) << endl;
	return JD;
}
void main() {
	struct tm tm;
	tm.tm_year = 2016 - 1900;
	tm.tm_mon = 5 - 1;
	tm.tm_mday = 7;
	tm.tm_hour = 16;
	tm.tm_min = 35;
	tm.tm_sec = 12;
	cout << to_string(DateTimeToJulianDate(tm)) << endl;
	system("pause");
}