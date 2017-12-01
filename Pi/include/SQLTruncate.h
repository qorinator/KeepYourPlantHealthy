#ifndef SQLTRUNCATE_H
#define SQLTRUNCATE_H

#include "SQLInterface.h"

class SQLTruncate : public SQLInterface
{
public:
	SQLTruncate();
	void GetAction(std::string const& msg) final;
private: 
	void TruncateTable(std::string const& msg);
};

#endif // SQLTRUNCATE_H