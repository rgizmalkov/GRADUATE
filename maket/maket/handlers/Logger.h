#pragma once
#include <fstream>
#include <string>
using namespace std;
class Logger
{
private:
	static Logger *obj;

	const string FILE = "logging.txt";
	ofstream logger;
	volatile int numberOfLine;

	Logger();
	Logger(const Logger&);
	Logger& operator=(Logger&);
public:
	~Logger();
	void write(string clazz, string method, string msg, string msg2);

	//singelton init
	static Logger * newInstanse() {
		if (!obj)
			obj = new Logger();
		return obj;
	};
};

