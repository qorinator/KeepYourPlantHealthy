#include "KYPHSensors.h"
#include "gtest/gtest.h"

class KYPHSensorsTest : public ::testing::Test {
protected:
	// Test Object
	std::vector<Package> packages;
	// Before every test
	virtual void SetUp() {
		Package* packageSoilMoisture = new Package();
		packageSoilMoisture->SetID(0x01);
		packageSoilMoisture->SetLength(0x02);
		packageSoilMoisture->SetData(0x02);
		packageSoilMoisture->SetData(0x58);
		packages.push_back(*packageSoilMoisture);
		delete packageSoilMoisture;
		packageSoilMoisture = nullptr;

		Package* packageDHT11 = new Package();
		packageDHT11->SetID(0x02);
		packageDHT11->SetLength(0x04);
		packageDHT11->SetData(0x19);
		packageDHT11->SetData(0x00);
		packageDHT11->SetData(0x1E);
		packageDHT11->SetData(0x00);
		packages.push_back(*packageDHT11);
		delete packageDHT11;
		packageDHT11 = nullptr;

		Package* packageUV = new Package();
		packageUV->SetID(0x03);
		packageUV->SetLength(0x01);
		packageUV->SetData(0x03);
		packages.push_back(*packageUV);
		delete packageUV;
		packageUV = nullptr;
		
	}
	// After every test
	virtual void TearDown() {
		packages.clear();
	}
	// Helper functions
};

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST_F(KYPHSensorsTest, CasePackagesAreCorrect) {
	KYPHSensors sensors(packages);
	ASSERT_EQ(sensors.GetUVLevel(), 3);
	ASSERT_EQ(sensors.GetTemperature(), 30.0);
	ASSERT_EQ(sensors.GetHumidity(), 25.0);
	ASSERT_EQ(sensors.GetSoilMoisture(), 600);
}