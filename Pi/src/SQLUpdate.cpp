#include "SQLUpdate.h"

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
		std::string date = row[0];
		std::string temperature = row[1];
		std::string humidity = row[2];
		std::string soilMoisture = row[3];
		std::string uv = row[4];

		std::cout << date << " |\t" << temperature << " |\t" 
		<< humidity << " |\t" << soilMoisture << " |\t" << uv;
		// std::cout << " |\t";
		// for(unsigned int i = 0; i < num_fields; i++)
		// 	std::cout << row[i] << "\t|\t";
		std::cout << std::endl;
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