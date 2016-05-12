#include "FileWriter.h"



FileWriter::FileWriter()
{
}


FileWriter::~FileWriter()
{
}

void FileWriter::write(string str) {
	ofs << str;
}
