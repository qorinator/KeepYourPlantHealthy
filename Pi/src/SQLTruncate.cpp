#include "SQLTruncate.h"

SQLTruncate::SQLTruncate() {}

void SQLTruncate::GetAction(std::string const& msg) {
	TruncateTable(msg);
}

void SQLTruncate::TruncateTable(std::string const& msg) {
	std::string query = "TRUNCATE " + msg + ";";
	if(!SendSQLQuery(query))		
		std::cout << "Error : unable to send MySQL querry" << std::endl;
}