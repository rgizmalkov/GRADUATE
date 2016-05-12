#pragma once
#include <fstream>
#include <string>
#include <map>
using namespace std;

class Properties
{
private:
	//Logger * logger;
	string file;
	map<string, string> prop;
	ifstream stream;
public:
	Properties(string file);
	Properties();
	static Properties* newInstance(string file);
	~Properties();
	string getValue(string property);
	
};

