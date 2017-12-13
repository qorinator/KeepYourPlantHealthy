#include "SensorUV.h"

SensorUV::SensorUV() {}

Package SensorUV::GetPackage() {
	ReadUVSensor();
	AppenDataToPackage();
	return _package;
}

void SensorUV::InitializeSensor(int sensorID) {
	if (sensorID == IDUVSensor) {
		while (!si114x.Begin())
			delay(1000);
	}	
}

void SensorUV::ReadUVSensor() {	
	_sensorValue.clear();
	int val = si114x.ReadUV();
	_sensorValue.push_back((val & 0xFF));	
}

void SensorUV::AppenDataToPackage() {
	_package.SetData(_sensorValue);
	_package.SetID(IDUVSensor);
	_package.SetLength(_sensorValue.size());
}