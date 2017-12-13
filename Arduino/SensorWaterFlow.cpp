#include "SensorWaterFlow.h"

SensorWaterFlow::SensorWaterFlow() {}

Package SensorWaterFlow::GetPackage() {
	ReadWaterFlowSensor();
	AppendPackageToData();
	return _package;
}

void SensorWaterFlow::InitializeSensor(int sensorID) {
	if(sensorID == IDWaterFlowSensor)
		_pin = PinWaterFlowSensor;
}

void SensorWaterFlow::ReadWaterFlowSensor() {
	_sensorValue.clear();
	int val = analogRead(_pin);
	_sensorValue.push_back((val & 0xFF00) >> 8);
	_sensorValue.push_back((val & 0xFF));
}

void SensorWaterFlow::AppendPackageToData() {
	_package.SetData(_sensorValue);
	_package.SetID(IDWaterFlowSensor);
	_package.SetLength(_sensorValue.size());
}