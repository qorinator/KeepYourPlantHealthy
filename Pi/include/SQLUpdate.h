#ifndef SQLUPDATE_H
#define SQLUPDATE_H

#include "SQLInterface.h"
#include "SQLObject.h"

#include <vector>

class SQLUpdate : public SQLInterface
{
public:
	SQLUpdate();
	void GetAction(std::string const& msg) final;
private: 
	void InitializeObjects();
	void StoreSensorMeasurement(std::string const& msg);
	void InitializeData(int index, MYSQL_ROW& row);
	bool IsDateNew(int index);
	void GetNewData(int index);
	void GetTableFromDatabase(std::string const& msg);
	bool GetRow(MYSQL_RES* results, MYSQL_ROW& row);
	std::string GetDate(std::string const& datetime);
	int GetElapsedMinute(std::string const& datetime);
private:
	static int const NumberOfSensors = 4;
	static std::string const SensorTables[NumberOfSensors];
	std::vector<SQLObject> _objects;
	std::vector<float> _sum;
	std::string _date;
	float _value;
	int _occurance;
};

#endif // SQLUPDATE_H