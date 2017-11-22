#include "SensorDHT11.h"

SensorDHT11::SensorDHT11() {}

Package SensorDHT11::GetPackage() {
	ReadDHT11();
	AppenDataToPackage();
	return _package;
}

void SensorDHT11::InitializeSensor(int sensorPin) {
	_pin = sensorPin;
}

void SensorDHT11::ReadDHT11() {
	_data.clear();
	if (GetDataFromDataBus())
		UpdateNewData();
	
}
bool SensorDHT11::GetDataFromDataBus() {
	if (IsDataBusStable()) {
		SendStartSignal();
		WaitForOutputReady();
		ReadDataBus();
		return true;
	}
	return false;
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

void SensorDHT11::UpdateNewData() {
	if (IsCheckSumOK()) {
		RemoveChecksumFromDataVector();
	}
	else
		_data.clear();
}
boolean SensorDHT11::IsCheckSumOK() {
	return ((_data[0] + _data[1] + _data[2] + _data[3]) == _data[4]);
}
void SensorDHT11::RemoveChecksumFromDataVector() {
	_data.pop_back();
}

void SensorDHT11::AppenDataToPackage() {
	_package.SetData(_data);
	_package.SetID(IDDHT11);
	_package.SetLength(_data.size());
}