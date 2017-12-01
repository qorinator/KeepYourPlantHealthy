#ifndef SQLUPDATE_H
#define SQLUPDATE_H

#include "SQLInterface.h"

class SQLUpdate : public SQLInterface
{
public:
	SQLUpdate();
	void GetAction(std::string const& msg) final;
private: 
	void StoreSensorMeasurement(std::string const& msg);
	void GetTableFromDatabase(std::string const& msg);
	bool GetRow(MYSQL_RES* results, MYSQL_ROW& row);
};

#endif // SQLUPDATE_H