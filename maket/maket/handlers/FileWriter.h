#pragma once
#include <fstream>
#include <string>
using namespace std;
class FileWriter
{
private:
	ofstream ofs;
public:
	FileWriter();
	void setFile(string val) { this->ofs.open(val); };
	void close() { this->ofs.close(); }
	~FileWriter();
	void write(string);
};

