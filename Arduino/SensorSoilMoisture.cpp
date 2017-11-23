#include "SensorSoilMoisture.h"

SensorSoilMoisture::SensorSoilMoisture() {}

Package SensorSoilMoisture::GetPackage() {
	ReadSoilMoistureSensor();
	AppendDataToPackage();
	return _package;
}

void SensorSoilMoisture::InitializeSensor(int sensorPin) {
	_pin = sensorPin;
}

void SensorSoilMoisture::ReadSoilMoistureSensor() {
	_data.clear();
	int val = analogRead(_pin);
	_data.push_back((val & 0xFF00) >> 8);
	_data.push_back((val & 0xFF));	
}

void SensorSoilMoisture::AppendDataToPackage() {
	_package.SetData(_data);
	_package.SetID(IDSoilMoistureSensor);
	_package.SetLength(_data.size());
}