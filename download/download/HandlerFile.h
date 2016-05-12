#pragma once
#include "Properties.h"
#include <vector>
#include <sstream>
#include <io.h>
#include <curl\curl.h>
#include "Date.h"
#define CURL_STATICLIB // используется статическая сборка библиотеки
#pragma comment(lib,"libcurl_x64.lib")

class HandlerFile
{
private:
	Properties* prop;
	string file;

	void changeDate(Date put, string file);
	static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
public:
	HandlerFile(string);
	~HandlerFile();

	//methods
	void download(string);
	
	//static methods
	static std::vector<std::string> split(const std::string &s, char delim);
	static bool fileExists(const char *fname);
};

