#include "ArduinoHandler.h"
#include "ProtocolUnwrapper.h"

#include <unistd.h>

ArduinoHandler::~ArduinoHandler() {	
	delete arduino;
	arduino	= nullptr;
}

ArduinoHandler::ArduinoHandler() {
	arduino = new SerialPort("/dev/ttyACM0", B115200);
	sleep(2);
	while(!GetSensorPackageFromArduino());
}

std::vector<Package> ArduinoHandler::GetPackage() {
	return SensorPackage;
}

bool ArduinoHandler::GetSensorPackageFromArduino() {
	arduino->SendDataRequest();
	if(arduino->IsMessageReceived()) {
		std::vector<unsigned int> rxBuffer =  arduino->ReadRXBuffer();

		ProtocolUnwrapper* unwrapper = new ProtocolUnwrapper(rxBuffer);
 		SensorPackage = unwrapper->GetPackages();

 		bool packageReady = false;

 		if(!SensorPackage.empty()) {
 			arduino->FlushRXBuffer();
 			packageReady = true;
 		}
 		
 		delete unwrapper;
 		unwrapper = nullptr;
 		return packageReady;
	}	
	return false;
}