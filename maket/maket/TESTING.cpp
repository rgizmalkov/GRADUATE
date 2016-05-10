#include "MySQL.h"
#include <mysql.h>
#include <string>
#include "Satellite.h"
#include <iostream>
using namespace std;
void main() {
	MySQL * sql = MySQL::newInstanse();
	string query = "SELECT * FROM SAT WHERE ID = 5 or ID = 11;";
	MYSQL_RES * result = sql->execute(query);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)) != NULL) {
		Satellite sat;
		sat.loadEntity(row);
		cout << sat.toString() << endl;
	}
	system("pause");
}
////////////////////////////////////////////