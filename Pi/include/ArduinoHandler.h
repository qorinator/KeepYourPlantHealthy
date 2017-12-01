#ifndef ARDUINOHANDLER_H
#define ARDUINOHANDLER_H

#include "SerialPort.h"
#include "Package.h"

class ArduinoHandler
{
public:
	ArduinoHandler();
	~ArduinoHandler();
	std::vector<Package> GetPackage();
private:
	bool GetSensorPackageFromArduino();	
private:
	SerialPort* arduino;
	std::vector<Package> SensorPackage;
};

#endif // ARDUINOHANDLER_H