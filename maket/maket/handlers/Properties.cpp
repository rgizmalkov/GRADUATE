#include "Properties.h"
#include "HandlerFile.h"


Properties::Properties() {}
//Constructor for prop: value(with out spaces)
Properties::Properties(string file)
{
	Properties::file = file;
	stream.open(file);
	string property;
	string value;
	while (!stream.eof()) {
		stream >> property;
		stream >> value;
		property = property.substr(0, property.size() - 1);
		prop.insert(pair<string, string>(property, value));
	}
}
//Constructor for prop: value(with spaces)
Properties* Properties::newInstance(string file) {
	Properties* prop = new Properties();
	prop->file = file;
	prop->stream.open(file);
	
	string val;
	string property;
	vector<string> vec;
	char buff[250];
	while (!prop->stream.eof()) {
		string value;
		prop->stream.getline(buff, 250);
		vec = HandlerFile::split(buff, ' ');
		property = vec[0];
		for (int i = 1; i < vec.size(); i++) {
			if (i != vec.size()-1) value += vec[i] + " ";
			else value += vec[i];
		}
		property = property.substr(0, property.size() - 1);
		prop->prop.insert(pair<string, string>(property, value));
	}
	return prop;
}

Properties::~Properties()
{
}

string Properties::getValue(string property) {
	return prop[property];
};
