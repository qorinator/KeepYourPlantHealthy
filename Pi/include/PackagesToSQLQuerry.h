#ifndef PACKAGESTOSQLQUERY_H
#define PACKAGESTOSQLQUERY_H

#include <string>

#include "Package.h"

class PackagesToSQLQuerry
{
public:
	PackagesToSQLQuerry(std::vector<Package> const& packages);
	~PackagesToSQLQuerry();
	std::string GetQuery();
private:
	void ConvertPackageToInsertDailySummaryQuerry(std::vector<Package> const& packages);
	std::string ToSQLString(int value);
	std::string ToSQLString(float value);
	std::string ToSQLString(std::string value);
private:
	std::string _query;
};

#endif // PACKAGESTOSQLQUERY_H