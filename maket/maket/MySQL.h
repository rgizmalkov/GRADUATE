#pragma once
#include <mysql.h>
#include <string>
#include <vector>
#include "Entity.h"
#include "Logger.h"
using namespace std;
#define _LCC_
#pragma comment (lib, "libmysql.lib")
class MySQL
{
private:
	static MySQL *sql;
	Logger *logger;
	const string clazz = "MySQL";

	string host;
	string user;
	string password;
	string schema;
	string port;

	MYSQL *connection, mysql;

	MySQL();
	MySQL(const MySQL&);
	MySQL& operator=(MySQL&);
	~MySQL();
public:
	//singelton init
	static MySQL* newInstanse() {
		if (!sql)
			sql = new MySQL();
		return sql;
	};

	MYSQL_RES * execute(string query);
	void query(string query);
};

