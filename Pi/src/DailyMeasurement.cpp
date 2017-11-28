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
	bool receive = false;
	while (!receive) {
		if(send) {			
			arduinoUSB.SendDataRequest();				
			send = false;		
		}
		if (arduinoUSB.IsMessageReceived()) {	
	 		rxBuffer = arduinoUSB.ReadRXBuffer();

	 		ProtocolUnwrapper* unwrapper = new ProtocolUnwrapper(rxBuffer);
	 		packages = unwrapper->GetPackages();
	 		if(!packages.empty()) {
	 			LocalTime localtime;
	 			KYPHSensors sensors(packages);	 			
	 			SQLInterface mySql(localtime.Get(), sensors);
	 			arduinoUSB.FlushRXBuffer();
	 			receive = true;
	 		}
	 		delete unwrapper;
	 		unwrapper = nullptr;
	 	}
	 	sleep(2);
	 }
	return 0;	
}
