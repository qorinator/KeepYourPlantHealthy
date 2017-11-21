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

class SensorDHT11 : public Sensor_i
{
public:
	 SensorDHT11();
	 std::vector<byte> GetValue() final;
	 void SetPin(int sensorPin) final;
private:
	void ReadDHT11();
	bool IsDataBusStable();
	void ReadDataBus();
	void SendStartSignal();
	void WaitForOutputReady();
	bool IsCheckSumOK();
	void RemoveChecksumFromDataVector();
private:
	static const uint8_t _dataLength = 5;
	boolean _firstReadFlag;
	unsigned long _poweredOnTime;
};


#endif // _SENSORDHT11_h

