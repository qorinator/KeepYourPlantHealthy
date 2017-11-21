#ifndef _SENSORUV_h
#define _SENSORUV_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor_i.h"

#include <SI114X\SI114X.h>
#include <Wire.h>

class SensorUV final
	: public Sensor_i
{
public:
	SensorUV();
	std::vector<byte> GetValue() final;
	void SetPin(int sensorPin) final;
private:
	void ReadUVSensor();
private:
	SI114X si114x;
};

#endif

