#include "KYPHSensors.h"

KYPHSensors::~KYPHSensors(){}

KYPHSensors::KYPHSensors(std::vector<Package> const& packages) {
	for(auto it = packages.begin(); it != packages.end(); ++it) {
		it->PrintPackage();		
	}
}


