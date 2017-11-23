#ifndef _SENSOR_I_h
#define _SENSOR_I_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Package.h"
#include <StandardCplusplus\StandardCplusplus.h>
#include <StandardCplusplus\vector>

#define PinSoilMoistureSensor	A1
#define PinDHT11Sensor			A0
#define PinButton				2
#define PinRotaryEncoderA		3
#define PinRotaryEncoderB		4
#define PinWaterFlowSensor		5
#define PinDummy				0

#define IDSoilMoistureSensor	1
#define IDDHT11					2
#define IDUVSensor				3
#define IDWaterFlowSensor		4

class Sensor_i
{
public:
	Sensor_i();
	virtual ~Sensor_i() = 0;
	virtual Package GetPackage() = 0;
	virtual void InitializeSensor(int sensorPin) = 0;
protected: 
	int _pin;
	std::vector<byte> _data;
	Package _package;
};

#endif

