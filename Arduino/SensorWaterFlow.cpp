#include "SensorWaterFlow.h"

SensorWaterFlow::SensorWaterFlow() {}

std::vector<byte> SensorWaterFlow::GetValue() {
	ReadWaterFlowSensor();
	Serial.print("Size of soil moisture data ");
	Serial.print(_data.size());
	Serial.print(" : ");
	Serial.print(_data[0]);
	Serial.print(", ");
	Serial.print(_data[1]);
	Serial.print("\r\n");
	return _data;
}

void SensorWaterFlow::SetPin(int sensorPin) {
	_pin = sensorPin;
}

void SensorWaterFlow::ReadWaterFlowSensor() {
	_data.clear();
	int val = analogRead(_pin);
	_data.push_back((val & 0xFF00) >> 8);
	_data.push_back((val & 0xFF));
}