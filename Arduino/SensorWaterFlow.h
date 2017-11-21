#ifndef _SENSORWATERFLOW_h
#define _SENSORWATERFLOW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor_i.h"

class SensorWaterFlow final
	: public Sensor_i
{
public:
	SensorWaterFlow();
	std::vector<byte> GetValue() final;
	void SetPin(int sensorPin) final;
private:
	void ReadWaterFlowSensor();
};

#endif // _SENSORWATERFLOW_h
