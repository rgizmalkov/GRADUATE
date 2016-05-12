#include "orm\MySQL.h"
#include <mysql.h>
#include <string>
#include "orm\Satellite.h"
#include <iostream>
#include "calculation\HandlerCalculation.h"
using namespace std;
void main1() {
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
void main() {
	MySQL * sql = MySQL::newInstanse();
	string query = "SELECT * FROM SAT WHERE ID = 5";
	MYSQL_RES * result = sql->execute(query);
	MYSQL_ROW row = mysql_fetch_row(result);
	Satellite* sat = new Satellite();
	sat->loadEntity(row);
	HandlerCalculation calc(sat);
	calc.calculat(86400., 1, "collision.collision");
	system("pause");
}
////////////////////////////////////////////
