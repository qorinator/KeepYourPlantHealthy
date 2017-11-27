#include <iostream>
#include <unistd.h>
#include <vector>

#include "SerialPort.h"
#include "ProtocolUnwrapper.h"
#include "SerialDataHandler.h"
#include "KYPHSensors.h"
#include "LocalTime.hpp"
#include "SQLInterface.h"

int main(int argc, char *argv[])
{
	SerialPort arduinoUSB("/dev/ttyACM0", B115200);
	std::vector<unsigned int> rxBuffer;
	std::vector<Package> packages;
	sleep(3);
	bool send = true;
	while (1) {
		if(send) {
			std::cout << "===============================" << std::endl; 
			arduinoUSB.SendDataRequest();
			send = false;
		}

		if (arduinoUSB.IsMessageReceived()) {			
	 		rxBuffer = arduinoUSB.ReadRXBuffer();

	 		ProtocolUnwrapper* unwrapper = new ProtocolUnwrapper(rxBuffer);
	 		packages = unwrapper->GetPackages();
	 		if(!packages.empty()) {
	 			// convert packages to sensor values
	 			LocalTime localtime;
	 			KYPHSensors sensors(packages);
	 			// send sensor values to MySQL database
	 			SQLInterface mySql(localtime.Get(), sensors);

	 			arduinoUSB.FlushRXBuffer();
	 			send = true;
	 		}
	 		delete unwrapper;
	 		unwrapper = nullptr;	 		
	 	}
	 	sleep(10);
	 }
	return 0;	
}
