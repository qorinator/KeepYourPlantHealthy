#include "ProtocolWrapper.h"
#include "Package.h"
#include "SensorUV.h"
#include "SensorWaterFlow.h"
#include "SensorSoilMoisture.h"
#include "SensorDHT11.h"
#include "Sensor_i.h"

#include <StandardCplusplus\StandardCplusplus.h>
#include <StandardCplusplus\vector>
#include <Wire.h>
#include <SI114X\SI114X.h>

std::vector<Sensor_i*> sensors;
std::vector<Package> packages;
std::vector<byte> message;

void setup() {
	Serial.begin(115200);
	sensors.push_back(new SensorSoilMoisture());	
	sensors.push_back(new SensorDHT11());
	sensors.push_back(new SensorUV());
	int id = 1;
	for (auto it = sensors.begin(); it != sensors.end(); ++it) {
		switch (id) {
		case IDSoilMoistureSensor:
			(*it)->InitializeSensor(PinSoilMoistureSensor);
			break;
		case IDDHT11:
			(*it)->InitializeSensor(PinDHT11Sensor);
			break;
		case IDUVSensor:
			(*it)->InitializeSensor(PinDummy);
			break;
		default:
			break;
		}
		id++;
	}
}

void loop() {
	packages.clear();
	message.clear();
	for (auto it = sensors.begin(); it != sensors.end(); ++it) {
		packages.push_back((*it)->GetPackage());
	}
	ProtocolWrapper* wrapper = new ProtocolWrapper(packages);
	message = wrapper->GetWrappedPackages();
	delete wrapper;
	wrapper = nullptr;

	Serial.print("size of message ");
	Serial.print(message.size());
	Serial.print(" : ");
	for (auto it = message.begin(); it != message.end(); ++it) {
		Serial.print(*it);
		Serial.print("  ");
	}
	Serial.print("\n");

	delay(5000);
}

