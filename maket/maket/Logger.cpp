#include "Logger.h"
Logger* Logger::obj = 0;


Logger::Logger()
{
	numberOfLine = 0;
	logger.open(FILE);
}


Logger::~Logger()
{
	logger.close();
}

void Logger::write(string clazz, string method, string msg, string msg2) {
	logger << to_string(numberOfLine++) + ":: " + "Class: " + clazz + "; " + "Method: " + method + "\n";
	logger << to_string(numberOfLine++) + ":: " + "Message: " + msg + "\n";
	if(!msg2.empty()) logger << to_string(numberOfLine++) + ":: " + "System message: " + msg2 + "\n";
}
