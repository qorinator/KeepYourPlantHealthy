#include "SQLInsert.h"

SQLInsert::SQLInsert() {}

void SQLInsert::GetAction(std::string const& msg) {
	InsertNewDataIntoTable(msg);
}

void SQLInsert::InsertNewDataIntoTable(std::string const& msg) {
	if(!SendSQLQuery(msg))		
		std::cout << "Error : unable to send MySQL querry" << std::endl;
}