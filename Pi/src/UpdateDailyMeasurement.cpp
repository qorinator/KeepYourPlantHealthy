#include <iostream>
#include <unistd.h>
#include <vector>

#include "ArduinoHandler.h"
#include "SQLQuery.h"
#include "SQLInterface.h"
#include "SQLInsert.h"

int main(int argc, char *argv[]) {

	ArduinoHandler* handler = new ArduinoHandler();
	SQLQuery* converter = new SQLQuery(handler->GetPackage());
	
	SQLInterface* mySQL = new SQLInsert();
	mySQL->GetAction(converter->GetQuery());

	delete handler;
	delete converter;
	delete mySQL;
	handler	= nullptr;
	converter = nullptr;
	mySQL = nullptr;

	return 0;	
}
