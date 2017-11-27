#include "SQLInterface.h"

SQLInterface::~SQLInterface() {
	mysql_close(_mysqlConnection);
	std::cout << "closing my sql" << std::endl;
}

SQLInterface::SQLInterface(std::string const& time, KYPHSensors const& sensors)
{	
	if(ConnectToMySQL()){
		if(ConnectToSensorValueDatabase()){
			DoSomething(time, sensors);
		}
		else
			std::cout << "connection is not successfull ?? " << std::endl;
	}
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

void SQLInterface::DoSomething(std::string const& time, KYPHSensors const& sensors) {
	std::string _time 			= "'" + time + "'";
	std::string temperature 	= "'" + std::to_string(sensors.GetTemperature()) + "'";
	std::string humidity 		= "'" + std::to_string(sensors.GetHumidity()) + "'";
	std::string soilMoisture 	= "'" + std::to_string(sensors.GetSoilMoisture()) + "'";
	std::string uv 				= "'" + std::to_string(sensors.GetUVLevel()) + "'";
	std::string msg = "INSERT INTO DailyMeasurement (datetime, temperature, humidity, moisture, uv) VALUES (" +
				 _time + ", " + temperature + ", " + humidity + ", " + soilMoisture + ", " + uv + ");";
	if(mysql_query(_mysqlConnection, msg.c_str()) != NULL)
		std::cout << "unable to insert" << std::endl;
	else
		std::cout << "insert is successfull" << std::endl;
	std::cout << "field count " << mysql_field_count(_mysqlConnection) << std::endl;
}