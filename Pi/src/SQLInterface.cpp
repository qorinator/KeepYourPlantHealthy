#include "SQLInterface.h"

SQLInterface::~SQLInterface() 
{
	mysql_close(_mysqlConnection);
}

SQLInterface::SQLInterface() 
{
	if(!InitializeSensorsValueDatabase())
		std::cout << "Error : unable to initialize connection to database." << std::endl;
}

bool SQLInterface::InitializeSensorsValueDatabase() {
	return (ConnectToMySQL() && ConnectToSensorValueDatabase());
}

bool SQLInterface::ConnectToMySQL() {
	_mysqlConnection = mysql_init(NULL);
	if(!_mysqlConnection)
		return false;
	else
		return true;
}

bool SQLInterface::ConnectToSensorValueDatabase() {	
	return (mysql_real_connect(
		_mysqlConnection, _server, _user, _password , _database , 0, NULL, 0) != NULL);
}

bool SQLInterface::SendSQLQuery(std::string msg) {
	return mysql_query(_mysqlConnection, msg.c_str()) == 0;
}