#include "SensorWaterFlow.h"

SensorWaterFlow::SensorWaterFlow() {}

Package SensorWaterFlow::GetPackage() {
	ReadWaterFlowSensor();
	AppendPackageToData();
	return _package;
}

void SensorWaterFlow::InitializeSensor(int sensorPin) {
	_pin = sensorPin;
}

void SensorWaterFlow::ReadWaterFlowSensor() {
	_data.clear();
	int val = analogRead(_pin);
	_data.push_back((val & 0xFF00) >> 8);
	_data.push_back((val & 0xFF));
}

void SensorWaterFlow::AppendPackageToData() {
	_package.SetData(_data);
	_package.SetID(IDWaterFlowSensor);
	_package.SetLength(_data.size());
}