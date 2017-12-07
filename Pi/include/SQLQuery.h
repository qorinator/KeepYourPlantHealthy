#ifndef PACKAGESTOSQLQUERY_H
#define PACKAGESTOSQLQUERY_H

#include <string>

#include "Package.h"
#include "SQLObject.h"

class SQLQuery
{
public:
	SQLQuery(std::vector<Package> const& packages);
	SQLQuery(SQLObject const& object);
	~SQLQuery();
	std::string GetQuery();
private:
	void ConvertPackageToInsertDailySummaryQuery(std::vector<Package> const& packages);
	void ConvertSQLObectToSQLQuery(SQLObject const& object);
	std::string ToSQLString(int value);
	std::string ToSQLString(float value);
	std::string ToSQLString(std::string value);
private:
	std::string _query;
};

#endif // PACKAGESTOSQLQUERY_H