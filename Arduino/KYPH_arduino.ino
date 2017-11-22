#include "PackageSorter.h"
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

Sensor_i* soilMoisture = new SensorSoilMoisture();
Sensor_i* dht11 = new SensorDHT11();
Sensor_i* uv = new SensorUV();

void setup() {
	Serial.begin(115200);
	soilMoisture->SetPin(PinSoilMoistureSensor);
	dht11->SetPin(PinDHT11Sensor);
	uv->SetPin(PinDummy);
}

void loop() {
	soilMoisture->GetPackage().PrintPackage();
	uv->GetPackage().PrintPackage();
	dht11->GetPackage().PrintPackage();

	delay(5000);
}
