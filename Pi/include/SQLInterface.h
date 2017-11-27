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
	SQLInterface(std::string const& time, KYPHSensors const& sensors);
	~SQLInterface();
private:
	bool ConnectToMySQL();
	bool ConnectToSensorValueDatabase();
	void DoSomething(std::string const& time, KYPHSensors const& sensors);
private:
	MYSQL* _mysqlConnection;
	const char* _server = "localhost";
	const char* _user = "kyph";
	const char* _password = "kyph";
	const char* _database = "SensorsValueDatabase";
};

#endif // SQLINTERFACE_H