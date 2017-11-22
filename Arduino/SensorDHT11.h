#ifndef _SENSORDHT11_h
#define _SENSORDHT11_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#if (F_CPU >= 7400000UL) && (F_CPU <= 9500000UL)	// 8 MHz(ish) AVR 
	#define COUNT 3
#elif (F_CPU >= 15400000UL) && (F_CPU <= 19000000L)	// 16 MHz(ish) AVR
	#define COUNT 6
#else
	#error "CPU SPEED NOT SUPPORTED"
#endif

#include "Sensor_i.h"
#include "Package.h"

class SensorDHT11 : public Sensor_i
{
public:
	 SensorDHT11();
	 void InitializeSensor(int sensorPin) final;
	 Package GetPackage() final;
private:
	void ReadDHT11();
	bool GetDataFromDataBus();
	bool IsDataBusStable();
	void SendStartSignal();	
	void WaitForOutputReady();
	void ReadDataBus();
	void UpdateNewData();
	bool IsCheckSumOK();
	void RemoveChecksumFromDataVector();
	void AppenDataToPackage();
private:
	static const uint8_t _dataLength = 5;
	boolean _firstReadFlag;
	unsigned long _poweredOnTime;
};

#endif // _SENSORDHT11_h

