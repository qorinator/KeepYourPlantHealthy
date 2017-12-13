#include "SensorSoilMoisture.h"

SensorSoilMoisture::SensorSoilMoisture() {}

Package SensorSoilMoisture::GetPackage() {
	ReadSoilMoistureSensor();
	AppendDataToPackage();
	return _package;
}

void SensorSoilMoisture::InitializeSensor(int sensorID) {
	if(sensorID == IDSoilMoistureSensor)
		_pin = PinSoilMoistureSensor;
}

void SensorSoilMoisture::ReadSoilMoistureSensor() {
	_sensorValue.clear();
	int val = analogRead(_pin);
	_sensorValue.push_back((val & 0xFF00) >> 8);
	_sensorValue.push_back((val & 0xFF));	
}

void SensorSoilMoisture::AppendDataToPackage() {
	_package.SetData(_sensorValue);
	_package.SetID(IDSoilMoistureSensor);
	_package.SetLength(_sensorValue.size());
}