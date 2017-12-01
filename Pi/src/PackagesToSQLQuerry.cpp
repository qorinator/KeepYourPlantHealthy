#include "PackagesToSQLQuerry.h"
#include "LocalTime.hpp"
#include "KYPHSensors.h"


PackagesToSQLQuerry::~PackagesToSQLQuerry() {}
PackagesToSQLQuerry::PackagesToSQLQuerry(std::vector<Package> const& packages) {
	
	ConvertPackageToInsertDailySummaryQuerry(packages);
}

void PackagesToSQLQuerry::ConvertPackageToInsertDailySummaryQuerry(std::vector<Package> const& packages) {
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

std::string PackagesToSQLQuerry::ToSQLString(int value) {
	return ("'" + std::to_string(value) + "'");
}
std::string PackagesToSQLQuerry::ToSQLString(float value) {
	return ("'" + std::to_string(value) + "'");
}
std::string PackagesToSQLQuerry::ToSQLString(std::string value) {
	return ("'" + value + "'");	
}

std::string PackagesToSQLQuerry::GetQuery() {
	return _query;
}