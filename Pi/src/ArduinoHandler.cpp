#include "ArduinoHandler.h"
#include "ProtocolUnwrapper.h"

#include <unistd.h>

ArduinoHandler::~ArduinoHandler() {	
	delete _arduino;
	_arduino	= nullptr;
}

ArduinoHandler::ArduinoHandler() {
	_arduino = new SerialPort("/dev/ttyACM0", B115200);
	sleep(2);
	while(!GetSensorPackageFromArduino());
}

std::vector<Package> ArduinoHandler::GetPackage() {
	return _sensorPackage;
}

bool ArduinoHandler::GetSensorPackageFromArduino() {
	_arduino->SendDataRequest();
	if(_arduino->IsMessageReceived()) {
		std::vector<unsigned int> rxBuffer =  _arduino->ReadRXBuffer();

		ProtocolUnwrapper* unwrapper = new ProtocolUnwrapper(rxBuffer);
 		_sensorPackage = unwrapper->GetPackages();

 		bool packageReady = false;

 		if(!_sensorPackage.empty()) {
 			_arduino->FlushRXBuffer();
 			packageReady = true;
 		}
 		
 		delete unwrapper;
 		unwrapper = nullptr;
 		return packageReady;
	}	
	return false;
}