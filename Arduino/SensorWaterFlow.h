#ifndef _SENSORWATERFLOW_h
#define _SENSORWATERFLOW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor_i.h"
#include "Package.h"

class SensorWaterFlow final
	: public Sensor_i
{
public:
	SensorWaterFlow();
	void InitializeSensor(int sensorPin) final;
	Package GetPackage() final;
private:
	void ReadWaterFlowSensor();
	void AppendPackageToData();
};

#endif // _SENSORWATERFLOW_h
