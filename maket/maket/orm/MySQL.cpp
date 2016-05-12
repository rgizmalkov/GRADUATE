#include "MySQL.h"
#pragma warning (disable : 4996)
void initVars(string& host, string& user, string& password, string& schema, string& port);
MySQL* MySQL::sql = 0;

MySQL::MySQL()
{
	logger = Logger::newInstanse();
	mysql_init(&mysql);
	initVars(host, user, password, schema, port);
	connection = mysql_real_connect(&mysql, host.c_str(),
		user.c_str(), password.c_str(), schema.c_str(), std::stoi(port), 0, 0);
	if (connection == NULL) {
		logger->write(clazz,"MySQL()", "Cannot connect to database. Check connection and try again!", mysql_error(connection));
		exit(-1);
	}
}


MySQL::~MySQL()
{
	delete connection;
	mysql_close(connection);
	delete sql;
}


MYSQL_RES * MySQL::execute(string query) {
	int query_state;
	query_state = mysql_query(connection, query.c_str());
	if (query_state != 0) {
		logger->write(clazz, "execute(string, vector)", "Cannot connect to database. Check connection and try again!", mysql_error(connection));
		exit(-1);
	}
	MYSQL_RES * results = mysql_store_result(connection);
	return results;
}

void MySQL::query(string query) {
	int query_state;
	query_state = mysql_query(connection, query.c_str());
	if (query_state != 0) {
		logger->write(clazz, "query(string)", "Cannot connect to database. Check connection and try again!", mysql_error(connection));
		exit(-1);
	}
};


void initVars(string& host, string& user, string& password, string& schema, string& port) {
	FILE *fset = fopen("mysql.config", "r");
	char buff[50];
	for (int i = 0; i < 5; i++) {
		fgets(buff, 50, fset);
		char *pch = strtok(buff, " ");
		char *pch1 = strtok(NULL, " \n");
		if (strcmp(pch, "host:") == 0) {
			host = std::string(pch1);
		}
		if (strcmp(pch, "user:") == 0) {
			user = std::string(pch1);
		}
		if (strcmp(pch, "password:") == 0) {
			password = std::string(pch1);
		}
		if (strcmp(pch, "schema:") == 0) {
			schema = std::string(pch1);
		}
		if (strcmp(pch, "port:") == 0) {
			port = std::string(pch1);
		}
	}
}