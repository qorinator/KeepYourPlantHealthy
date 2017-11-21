// SensorSoilMoisture.h

#ifndef _SENSORSOILMOISTURE_h
#define _SENSORSOILMOISTURE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor_i.h"

class SensorSoilMoisture final
	: public Sensor_i
{
 public:
	 SensorSoilMoisture();
	 std::vector<byte> GetValue() final;
	 void SetPin(int sensorPin) final;
private:
	void ReadSoilMoistureSensor();
};

#endif

