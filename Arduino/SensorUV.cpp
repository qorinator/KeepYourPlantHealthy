#include "SensorUV.h"

SensorUV::SensorUV() {}

std::vector<byte> SensorUV::GetValue() {
	ReadUVSensor();
	Serial.print("Size of UV data ");
	Serial.print(_data.size());
	Serial.print(" : ");
	Serial.print(_data[0]);
	Serial.print("\r\n");
	return _data;
}

void SensorUV::SetPin(int sensorPin) {
	while (!si114x.Begin())
		delay(1000);
}

void SensorUV::ReadUVSensor() {	
	_data.clear();
	int val = si114x.ReadUV();
	_data.push_back((val & 0xFF));
}