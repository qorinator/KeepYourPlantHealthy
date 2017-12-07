#include "SQLQuery.h"
#include "LocalTime.hpp"
#include "KYPHSensors.h"


SQLQuery::~SQLQuery() {}
SQLQuery::SQLQuery(std::vector<Package> const& packages) {	
	ConvertPackageToInsertDailySummaryQuery(packages);
}
SQLQuery::SQLQuery(SQLObject const& object) {
	ConvertSQLObectToSQLQuery(object);
}

void SQLQuery::ConvertPackageToInsertDailySummaryQuery(std::vector<Package> const& packages) {
	LocalTime localtime;
	KYPHSensors sensors(packages);

	std::string _time 			= ToSQLString(localtime.Get());
	std::string temperature 	= ToSQLString(sensors.GetTemperature());
	std::string humidity 		= ToSQLString(sensors.GetHumidity());
	std::string soilMoisture 	= ToSQLString(sensors.GetSoilMoisture());
	std::string uv 				= ToSQLString(sensors.GetUVLevel());

	_query = "INSERT INTO DailyMeasurement (datetime, temperature, humidity, moisture, uv) VALUES ("
	  		 + _time + ", " 
			 + temperature + ", " 
			 + humidity + ", " 
			 + soilMoisture + ", " 
			 + uv + ");";
}

void SQLQuery::ConvertSQLObectToSQLQuery(SQLObject const& object) {
	std::string date 	= ToSQLString(object.GetDate());
	std::string name 	= ToSQLString(object.GetName());
	std::string average = ToSQLString(object.GetAverage());
	std::string minimum = ToSQLString(object.GetMinimum());
	std::string maximum = ToSQLString(object.GetMaximum());

	_query = "INSERT INTO " + name + " (datetime, average, minimum, maximum) VALUES ("
	  		 + date + ", " 
			 + average + ", " 
			 + minimum + ", " 			 
			 + maximum + ");";	
}


std::string SQLQuery::ToSQLString(int value) {
	return ("'" + std::to_string(value) + "'");
}
std::string SQLQuery::ToSQLString(float value) {
	return ("'" + std::to_string(value) + "'");
}
std::string SQLQuery::ToSQLString(std::string value) {
	return ("'" + value + "'");	
}

std::string SQLQuery::GetQuery() {
	return _query;
}