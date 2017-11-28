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
	bool InitializeSensorsValueDatabase();
	bool ConnectToMySQL();
	bool ConnectToSensorValueDatabase();	
	void AppendSensorsValueToTable(std::string const& time, KYPHSensors const& sensors);
	bool SendSQLQuery(std::string msg);
	std::string ToSQLString(int value);
	std::string ToSQLString(float value);
	std::string ToSQLString(std::string value);
private:
	MYSQL* _mysqlConnection;
	const char* _server = "localhost";
	const char* _user = "kyph";
	const char* _password = "kyph";
	const char* _database = "SensorsValueDatabase";
};

#endif // SQLINTERFACE_H