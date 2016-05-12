#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Date.h"
#include "Properties.h"
#include "HandlerFile.h"
#pragma warning (disable : 4996)
using namespace std;
string read1(int size, string date) {
	int dsize = date.size();
	if (dsize < size) return "0x0";
	string ret = date.substr(0, size);
	date = date.substr(size, dsize);
	return ret;
}
void main() {
	HandlerFile hf("setting.properties");
	hf.download("test");
	//system("pause");
}