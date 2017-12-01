#include "SQLInterface.h"
#include "SQLTruncate.h"

#include <iostream>

int main(int argc, char *argv[]) {	
	SQLInterface* mySQL = new SQLTruncate();
	mySQL->GetAction("DailyMeasurement");
	delete mySQL;
	mySQL = nullptr;
	return 0;
}