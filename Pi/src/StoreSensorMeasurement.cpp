#include "SQLInterface.h"
#include "SQLUpdate.h"

#include <iostream>

int main(int argc, char *argv[]) {	
	SQLInterface* mySQL = new SQLUpdate();
	mySQL->GetAction("DailyMeasurement");
	delete mySQL;
	mySQL = nullptr;
	return 0;
}