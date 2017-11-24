#ifndef KYPHSENSORS_H
#define KYPHSENSORS_H

#include "Package.h"

#include <vector>
#include <iostream>

enum class SensorTag {
	SoilMoisture,
	DHT11,
	UV,
	WaterFlow 
}

class KYPHSensors
{
public:
	KYPHSensors(std::vector<Package> const& packages);
	~KYPHSensors();
private:
	float _temperature;
	float _humidity;
	int _soilMoisture;
	int _uvLevel;
};

#endif // KYPHSENSORS_H