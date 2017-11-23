#ifndef _SENSORSOILMOISTURE_h
#define _SENSORSOILMOISTURE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor_i.h"
#include "Package.h"

class SensorSoilMoisture final
	: public Sensor_i
{
public:
	SensorSoilMoisture();
	Package GetPackage() final;
	void InitializeSensor(int sensorPin) final;
private:
	void ReadSoilMoistureSensor();
	void AppendDataToPackage();
};

#endif

