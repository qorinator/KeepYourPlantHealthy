#include "SQLQuery.h"
#include "LocalTime.hpp"
#include "gtest/gtest.h"

#include <string>

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(SQLQueryTest, CaseDailyMeasurement) {
	std::vector<Package> packages;

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

	SQLQuery query(packages);
	LocalTime time;
	std::string str = "INSERT INTO DailyMeasurement (datetime, temperature, humidity, moisture, uv) VALUES ('" + time.Get() + "', '30.000000', '25.000000', '600', '3');";
	ASSERT_EQ(query.GetQuery(), str);
}


TEST(SQLQueryTest, CaseSQLObject) {
	SQLObject object("temperature");
	LocalTime time;
	object.InitializeValues(time.Get(), 14);
	object.SetValues(0, 12);
	object.SetValues(0, 13);
	object.SetValues(13, 15);

	SQLQuery query(object);
	
	std::string str = "INSERT INTO temperature (date, average, minimum, maximum) VALUES ('" + time.Get() + "', '13.000000', '12.000000', '15.000000');";
	ASSERT_EQ(query.GetQuery(), str);
}