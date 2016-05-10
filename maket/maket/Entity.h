#pragma once
#include <mysql.h>
class Entity
{
public:
	virtual Entity* loadEntity(MYSQL_ROW row) {	return NULL; };
	virtual void saveEntity() {};
	virtual void dropEntity() {};
	virtual void updateEntity() {};
	Entity();
	~Entity();
};

