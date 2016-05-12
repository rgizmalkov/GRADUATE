#include "Date.h"
#include "HandlerFile.h"
const string Date::DB_FORMAT = "%Y-%M-%d %h:%m:%s";
const string Date::DATE= "%Y-%M-%d";
const string Date::TIME = "%h:%m:%s";

Date::Date()
{

}
Date::Date(tm tm) {
	mtime = tm;
	stime = to_string(tm.tm_year) + "-" + to_string(tm.tm_mon) + "-" + to_string(tm.tm_mday) + " " + to_string(tm.tm_hour) + ":" + to_string(tm.tm_min) + ":" + to_string(tm.tm_sec);
};
Date::Date(double jd) {
	setFromJulDateToDateTime(jd);
	stime = to_string(mtime.tm_year) + "-" + to_string(mtime.tm_mon) + "-" + to_string(mtime.tm_mday) + " " + to_string(mtime.tm_hour) + ":" + to_string(mtime.tm_min) + ":" + to_string(mtime.tm_sec);
};
Date::Date(string& _time, string format) {
	stime = _time;
	vector<string> form = HandlerFile::split(format, '%');
	for (int i = 1; i < form.size(); i++) {
		string f = form[i];
		int fsize = f.size();
		switch (fsize) {
			case 1:
				setDate(f[0], _time);
				break;
			case 2:
				setDate(f[0], _time);
				setDate(f[1], _time);
				break;
		}
	}
};
Date* Date::newInstance() {
	Date* date = new Date();
	time_t t = time(NULL);
	struct tm mtime = *localtime(&t);
	mtime.tm_year += 1900;
	mtime.tm_mon += 1;
	date->setTime(mtime);
	date->stime = to_string(date->mtime.tm_year) + "-" + to_string(date->mtime.tm_mon) + "-" + to_string(date->mtime.tm_mday) + " " + to_string(date->mtime.tm_hour) + ":" + to_string(date->mtime.tm_min) + ":" + to_string(date->mtime.tm_sec);
	return date;
};
Date::~Date()
{
}
long Date::operator-(Date date) {
	tm tm1 = { mtime.tm_sec, mtime.tm_min, mtime.tm_hour, mtime.tm_mday, mtime.tm_mon - 1, mtime.tm_year - 1900, 0, 0, 0 };
	time_t t1 = mktime(&tm1);
	tm tm2 = { date.mtime.tm_sec, date.mtime.tm_min, date.mtime.tm_hour, date.mtime.tm_mday, date.mtime.tm_mon - 1, date.mtime.tm_year - 1900, 0, 0, 0 };
	time_t t2 = mktime(&tm2);
	time_t dif;
	if(t1 > t2) dif = (t1 - t2);
	else dif = (t2 - t1);
	return dif;
}

string read(int size, string& date) {
	int dsize = date.size();
	if (dsize < size) return "0x0";
	string ret = date.substr(0, size);
	date = date.substr(size, dsize);
	return ret;
}
string Date::getFTime(string format) {
	string output;
	vector<string> form = HandlerFile::split(format, '%');
	for (int i = 1; i < form.size(); i++) {
		string f = form[i];
		int fsize = f.size();
		switch (fsize) {
		case 1:
			output += getDate(f[0]);
			break;
		case 2:
			output += getDate(f[0]);
			output += f[1];
			break;
		}
	}
	return output;
};
string Date::getDate(char f) {
	switch (f)
	{
	case 'Y':
		return to_string(mtime.tm_year);
	case 'M':
		return to_string(mtime.tm_mon);
	case 'd':
		return to_string(mtime.tm_mday);
	case 'h':
		return to_string(mtime.tm_hour);
	case 'm':
		return to_string(mtime.tm_min);
	case 's':
		return to_string(mtime.tm_sec);
	}
}
void Date::setDate(char f, string& date) {
	int size;
	switch (f)
	{
	case 'Y':
		size = 4;
		mtime.tm_year = stoi(read(size, date));
		break;
	case 'M':
		size = 2;
		mtime.tm_mon = stoi(read(size, date));
		break;
	case 'd':
		size = 2;
		mtime.tm_mday = stoi(read(size, date));
		break;
	case 'h':
		size = 2;
		mtime.tm_hour = stoi(read(size, date));
		break;
	case 'm':
		size = 2;
		mtime.tm_min = stoi(read(size, date));
		break;
	case 's':
		size = 2;
		mtime.tm_sec = stoi(read(size, date));
		break;
	default:
		size = 1;
		read(size, date);
		break;
	}
}

double Date::dateTimeToJulianDate() {
	int year = mtime.tm_year + 1900;
	//-----> number of seconds sience 1970
	//int year = 1970 + int(time / 31557600);
	int A = int(year / 100);
	int B = 2 - A + int(A / 4);
	int M = mtime.tm_mon + 1;
	if (M <= 2) {
		year = year - 1;
		M = M + 12;
	}
	double JD = int(365.25 * (year + 4716)) + int(30.6001 * (M + 1)) + mtime.tm_mday + B - 1524.5;
	JD += (double)mtime.tm_hour / (double)24 + (double)mtime.tm_min / (double)(24 * 60) + (double)mtime.tm_sec / (double)(24 * 3600);
	return JD;
}

void Date::setFromJulDateToDateTime(double JD) {
	int Year, Month, Day, Hour, Min, Sec;
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
	mtime.tm_sec = Sec;
	mtime.tm_min = Min;
	mtime.tm_hour = Hour;
	mtime.tm_mday = Day;
	mtime.tm_mon = Month;
	mtime.tm_year = Year;
}


