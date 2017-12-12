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
	SerialPort* _arduino;
	std::vector<Package> _sensorPackage;
};

#endif // ARDUINOHANDLER_H