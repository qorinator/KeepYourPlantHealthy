#include "KYPHSensors.h"

#include <iostream>
KYPHSensors::~KYPHSensors(){}

KYPHSensors::KYPHSensors(std::vector<Package> const& packages) 
	: _temperature(0)
	, _humidity(0)
	, _soilMoisture(0)
	, _uvLevel(0)
{
	for(auto it = packages.begin(); it != packages.end(); ++it)
		ConvertPackagesToValue(*it);
}

void KYPHSensors::ConvertPackagesToValue(Package const& package) {
	std::vector<unsigned int> data = package.GetData();
	switch(package.GetID()) {
	case idSoilMoistureSensor:			
		_soilMoisture = (data[0] << 8) + data[1];
		break;
	case idDHT11:			
		_humidity = data[0] + data[1]/10.0;
		_temperature = data[2] + data[3]/10.0;
		break;
	case idUVSensor:
		_uvLevel = data[0];		
		break;
	case idWaterFlowSensor:
		std::cout << "Water flow sensor : " << std::endl;
		break;
	default:
		break;
	}	
}

float KYPHSensors::GetTemperature() const {
	return _temperature;
}

float KYPHSensors::GetHumidity() const {
	return _humidity;
}

int KYPHSensors::GetSoilMoisture() const{
	return _soilMoisture;
}

int KYPHSensors::GetUVLevel() const {
	return _uvLevel;
}

