#include "SerialDataHandler.h"
#include "gtest/gtest.h"

class SerialDataHandlerTest : public ::testing::Test {
protected:
	// Test Object
	std::vector<unsigned int> buffer;
	// Before every test
	virtual void SetUp() {
		buffer.push_back(0x00);	// 0
		buffer.push_back(0xF0);
		buffer.push_back(0x0F);
		buffer.push_back(0x03);

		buffer.push_back(0x00); // 4
		buffer.push_back(0x01);
		buffer.push_back(0x02);
		buffer.push_back(0x02);
		buffer.push_back(0x58);

		buffer.push_back(0x00); // 9
		buffer.push_back(0x02);
		buffer.push_back(0x04);
		buffer.push_back(0x19);
		buffer.push_back(0x00);
		buffer.push_back(0x1E);
		buffer.push_back(0x00);

		buffer.push_back(0x00);	// 16
		buffer.push_back(0x03);
		buffer.push_back(0x01);
		buffer.push_back(0x03);

		buffer.push_back(0x00); // 20
		buffer.push_back(0xA3);
	}
	// After every test
	virtual void TearDown() {
		buffer.empty();
	}
	// Helper functions
};

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST_F(SerialDataHandlerTest, CaseMessageIsReady) {
	SerialDataHandler handler(buffer);	
	ASSERT_TRUE(handler.IsMessageReady());	
}

TEST_F(SerialDataHandlerTest, CaseDataIndexIsFound) {
	std::vector<int> dataIndex;
	dataIndex.push_back(4);
	dataIndex.push_back(9);
	dataIndex.push_back(16);	
	SerialDataHandler handler(buffer);	
	ASSERT_EQ(handler.GetDataIndex(), dataIndex);	
}

TEST_F(SerialDataHandlerTest, CaseWrongStartMessage) {
	buffer[2] = 0x0E;
	SerialDataHandler handler(buffer);	
	ASSERT_FALSE(handler.IsMessageReady());		
}

TEST_F(SerialDataHandlerTest, CaseMessageIsFragmented) {
	buffer.resize(buffer.size() - 4);

	SerialDataHandler handler(buffer);	
	ASSERT_FALSE(handler.IsMessageReady());		
}

TEST_F(SerialDataHandlerTest, CaseNumberOfPackageisTooSmall) {
	buffer[3] = 0x02;

	SerialDataHandler handler(buffer);	
	ASSERT_FALSE(handler.IsMessageReady());		
}

TEST_F(SerialDataHandlerTest, CaseNumberOfPackageisTooBig) {
	buffer[3] = 0x04;

	SerialDataHandler handler(buffer);	
	ASSERT_FALSE(handler.IsMessageReady());		
}

TEST_F(SerialDataHandlerTest, CaseWrongChecksum) {
	buffer[21] = 0x04;

	SerialDataHandler handler(buffer);	
	ASSERT_FALSE(handler.IsMessageReady());		
}