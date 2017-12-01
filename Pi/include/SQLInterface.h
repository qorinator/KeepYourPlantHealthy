#ifndef SQLINTERFACE_H
#define SQLINTERFACE_H

#include "LocalTime.hpp"
#include "KYPHSensors.h"

#include <mysql.h>
#include <iostream>
#include <string>

class SQLInterface
{
public:
	SQLInterface();
	virtual ~SQLInterface() = 0;
	virtual void GetAction(std::string const& msg) = 0;		
private:
	bool InitializeSensorsValueDatabase();
	bool ConnectToMySQL();
	bool ConnectToSensorValueDatabase();
protected:
	bool SendSQLQuery(std::string msg);
protected:
	MYSQL* _mysqlConnection;
private:
	const char* _server = "localhost";
	const char* _user = "kyph";
	const char* _password = "kyph";
	const char* _database = "SensorsValueDatabase";
};

#endif // SQLINTERFACE_H