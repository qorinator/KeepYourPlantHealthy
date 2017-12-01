#ifndef SQLINSERT_H
#define SQLINSERT_H

#include "SQLInterface.h"

class SQLInsert : public SQLInterface
{
public:
	SQLInsert();
	void GetAction(std::string const& msg) final;
private:
	void InsertNewDataIntoTable(std::string const& msg);
};

#endif // SQLINSERT_H