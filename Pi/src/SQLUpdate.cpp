#include "SQLUpdate.h"

std::string const SQLUpdate::SensorTables[4] = {"TemperatureMeasurement", "HumidityMeasurement",
									 			"MoistureMeasurement", "UVMeasurement"};

SQLUpdate::SQLUpdate() {}

void SQLUpdate::GetAction(std::string const& msg) {
	StoreSensorMeasurement(msg);
}
void SQLUpdate::StoreSensorMeasurement(std::string const& msg) {
	GetTableFromDatabase(msg);

	MYSQL_RES* results;
	MYSQL_ROW row;
	unsigned int num_fields = mysql_field_count(_mysqlConnection);

	results = mysql_store_result(_mysqlConnection);	
	while(GetRow(results, row)) {
		std::string query;
		for(unsigned int i = 1; i < num_fields; i++) {
			query = "INSERT INTO " + SensorTables[i-1] + " (date, value) VALUES ('" + row[0] + "', '" + row[i] + "'); ";
			if(!SendSQLQuery(query))		
				std::cout << "Error : unable to send MySQL querry" << std::endl;
		}
	}
}

void SQLUpdate::GetTableFromDatabase(std::string const& msg) {
	std::string query = "SELECT * from " + msg + ";";
	if(!SendSQLQuery(query))		
		std::cout << "Error : unable to send MySQL querry" << std::endl;
}

bool SQLUpdate::GetRow(MYSQL_RES* results, MYSQL_ROW& row) {
	row = mysql_fetch_row(results);
	return (row != NULL);
}