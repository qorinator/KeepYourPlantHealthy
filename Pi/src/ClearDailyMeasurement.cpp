#include "SQLInterface.h"

#include <iostream>

int main(int argc, char *argv[]) {	
	SQLInterface* mySQL = new SQLInterface();
	mySQL->TruncateDailyMeasurementQuery();
	delete mySQL;
	mySQL = nullptr;
	return 0;
}