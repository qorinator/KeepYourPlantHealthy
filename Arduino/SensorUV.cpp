#include "SensorUV.h"

SensorUV::SensorUV() {}

Package SensorUV::GetPackage() {
	ReadUVSensor();
	AppenDataToPackage();
	return _package;
}

void SensorUV::InitializeSensor(int sensorPin) {
	while (!si114x.Begin())
		delay(1000);
}

void SensorUV::ReadUVSensor() {	
	_data.clear();
	int val = si114x.ReadUV();
	_data.push_back((val & 0xFF));	
}

void SensorUV::AppenDataToPackage() {
	_package.SetData(_data);
	_package.SetID(IDDHT11);
	_package.SetLength(_data.size());
}