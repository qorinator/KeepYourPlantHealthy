#ifndef KYPHSENSORS_H
#define KYPHSENSORS_H

#include "Package.h"

#include <vector>
#include <iostream>

class KYPHSensors
{
public:
	KYPHSensors(std::vector<Package> const& packages);
	~KYPHSensors();
	float GetTemperature() const;
	float GetHumidity() const;
	int GetSoilMoisture() const;
	int GetUVLevel() const;
private:
	void ConvertPackagesToValue(Package const& package);
private:
	float _temperature;
	float _humidity;
	int _soilMoisture;
	int _uvLevel;
	static const int idSoilMoistureSensor =  1;
	static const int idDHT11 = 2;
	static const int idUVSensor = 3;
	static const int idWaterFlowSensor = 4;
};

#endif // KYPHSENSORS_H