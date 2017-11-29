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

SQLInterface::SQLInterface(std::string const& time, KYPHSensors const& sensors)
{	
	if(InitializeSensorsValueDatabase())
		AppendSensorsValueToTable(time, sensors);
	else
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

void SQLInterface::AppendSensorsValueToTable(std::string const& time, KYPHSensors const& sensors) {
	std::string _time 			= ToSQLString(time);
	std::string temperature 	= ToSQLString(sensors.GetTemperature());
	std::string humidity 		= ToSQLString(sensors.GetHumidity());
	std::string soilMoisture 	= ToSQLString(sensors.GetSoilMoisture());
	std::string uv 				= ToSQLString(sensors.GetUVLevel());
	std::string msg = "INSERT INTO DailyMeasurement (datetime, temperature, humidity, moisture, uv) VALUES ("
					   + _time + ", " 
					   + temperature + ", " 
					   + humidity + ", " 
					   + soilMoisture + ", " 
					   + uv + ");";
	if(!SendSQLQuery(msg))		
		std::cout << "Error : unable to send MySQL querry" << std::endl;
}

void SQLInterface::TruncateDailyMeasurementQuery() {
	std::string msg = "TRUNCATE DailyMeasurement;";
	if(!SendSQLQuery(msg))		
		std::cout << "Error : unable to send MySQL querry" << std::endl;
}

bool SQLInterface::SendSQLQuery(std::string msg) {
	return mysql_query(_mysqlConnection, msg.c_str()) == 0;
}

std::string SQLInterface::ToSQLString(int value) {
	return ("'" + std::to_string(value) + "'");
}
std::string SQLInterface::ToSQLString(float value) {
	return ("'" + std::to_string(value) + "'");
}
std::string SQLInterface::ToSQLString(std::string value) {
	return ("'" + value + "'");	
}