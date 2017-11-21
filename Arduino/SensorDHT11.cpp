#include "SensorDHT11.h"

SensorDHT11::SensorDHT11()
{}

std::vector<byte> SensorDHT11::GetValue() {
	ReadDHT11();
	return _data;
}

void SensorDHT11::SetPin(int sensorPin) {
	_pin = sensorPin;
}

void SensorDHT11::ReadDHT11() {
	_data.clear();
	if (IsDataBusStable()) {
		SendStartSignal();
		WaitForOutputReady();
		ReadDataBus();
	}
	if (IsCheckSumOK())
		RemoveChecksumFromDataVector();
	else
		_data.clear();
	Serial.print("Size of DHT11 data ");
	Serial.print(_data.size());
	Serial.print(" : ");
	Serial.print(_data[0]);
	Serial.print(", ");
	Serial.print(_data[1]);
	Serial.print(", ");
	Serial.print(_data[2]);
	Serial.print(", ");
	Serial.print(_data[3]);
	Serial.print("\r\n");
}

bool SensorDHT11::IsDataBusStable() {
	if (_firstReadFlag) {
		unsigned long currentReadingDuration = millis();
		if ((currentReadingDuration-_poweredOnTime) < 2000)
			return false;
		else
			return true;
		_firstReadFlag = false;
	}
	else
		return true;
}
void SensorDHT11::SendStartSignal() {
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delay(20);
}
void SensorDHT11::WaitForOutputReady() {
	digitalWrite(_pin, HIGH);
	delayMicroseconds(40);
	pinMode(_pin, INPUT);
	while (digitalRead(_pin) == LOW);	// response signal
	while (digitalRead(_pin) == HIGH);	// pulled ready for output

}
void SensorDHT11::ReadDataBus()
{
	// This function is time sensitive do not put any
	// serial.printxx inside the while loop
	// or else the data that is received will be faulty
	uint8_t dataIndex = 0;
	uint8_t bitIndexCounter = 0;
	byte receivedData = 0;
	unsigned long tStart, tEnd;	
	while (dataIndex < _dataLength)
	{
		while (digitalRead(_pin) == LOW);	// start to transmit 1-bit data
		tStart = micros();
		while (digitalRead(_pin) == HIGH);	// data '0' or '1'
		tEnd = micros();
		if ((tEnd - tStart) > 50)			// if duration > 50 received bit = '1' else '0'
			receivedData = (receivedData << 1) + 1;
		else
			receivedData = (receivedData << 1) + 0;
		bitIndexCounter++;
		if (bitIndexCounter >= 8) {
			_data.push_back(receivedData);
			dataIndex++;
			bitIndexCounter = 0;
			receivedData = 0;
		}
	}	
}
boolean SensorDHT11::IsCheckSumOK() {
	return ((_data[0] + _data[1] + _data[2] + _data[3]) == _data[4]);
}
void SensorDHT11::RemoveChecksumFromDataVector() {
	_data.pop_back();
}