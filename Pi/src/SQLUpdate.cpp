#include "SQLUpdate.h"
#include "SQLQuery.h"
#include <unistd.h>

std::string const SQLUpdate::SensorTables[NumberOfSensors] = {"temperature",
															  "humidity",
															  "moisture",
															  "uv"};

SQLUpdate::SQLUpdate()
	: _value(0)
	, _occurance(1)
{}

void SQLUpdate::GetAction(std::string const& msg) {
	InitializeObjects();
	StoreSensorMeasurement(msg);
}

void SQLUpdate::InitializeObjects() {
	for(unsigned int i = 0; i < NumberOfSensors; i++){
		_objects.push_back(SQLObject(SensorTables[i]));
		_sum.push_back(0);		
	}
}

void SQLUpdate::StoreSensorMeasurement(std::string const& msg) {
	GetTableFromDatabase(msg);

	MYSQL_RES* results;
	MYSQL_ROW row;
	results = mysql_store_result(_mysqlConnection);
		
	while(GetRow(results, row)) {
		for(unsigned int i = 0; i < NumberOfSensors; i++) {					
			InitializeData(i, row);
			GetNewData(i);
			if(GetElapsedMinute(row[0]) >= (12 * 60 + 00)){	
				SQLQuery* converter = new SQLQuery(_objects[i]);
				std::cout << converter->GetQuery() << std::endl;
				if(!SendSQLQuery(converter->GetQuery()))
					std::cout << "Error : unable to send MySQL querry" << std::endl;
				delete converter;
				converter = nullptr;
			}			
		}
		_occurance++;
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

void SQLUpdate::InitializeData(int index, MYSQL_ROW& row) {
	_date = row[0];
	_value = atof(row[index+1]);
	if(IsDateNew(index)){
		_objects[index].InitializeValues(GetDate(_date), _value);
		_sum[index] = 0;
		_occurance = 1;
	}
}

void SQLUpdate::GetNewData(int index) {	
	if(!IsDateNew(index)){
		_sum[index] += _value;
		_objects[index].SetValues((_sum[index]/_occurance), _value);
	}	
}

bool SQLUpdate::IsDateNew(int index) {
	return (_objects[index].GetDate() != GetDate(_date));
}

std::string SQLUpdate::GetDate(std::string const& datetime) {
	return (datetime.substr(0, datetime.find(' ')));
}

int SQLUpdate::GetElapsedMinute(std::string const& datetime) {
	std::string time = datetime.substr(datetime.find(' ') + 1);
	int hour = atoi(time.substr(0, time.find(':')).c_str());
	int minute = atoi(time.substr(time.find(':')+1, time.find(':')).c_str());
	return hour * 60 + minute;
}
