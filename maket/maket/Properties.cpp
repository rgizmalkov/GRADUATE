#include "Properties.h"



Properties::Properties(string file)
{
	Properties::file = file;
	stream.open(file);
	string property;
	string value;
	while (!stream.eof()) {
		stream >> property;
		stream >> value;
		prop.insert(pair<string, string>(property, value));
	}
}

Properties::~Properties()
{
}

string Properties::getValue(string property) {
	return prop[property];
};
