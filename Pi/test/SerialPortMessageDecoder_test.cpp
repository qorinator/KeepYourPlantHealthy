#include "MessageDecoder.h"
#include "gtest/gtest.h"

class MessageDecoderTest : public ::testing::Test {
protected:
	// Test Object
	MessageDecoder* decoder;	
	// Before every test
	virtual void SetUp() {			
	 	decoder = new MessageDecoder();
	}
	// After every test
	virtual void TearDown() {
		delete decoder;
		decoder = nullptr;
	}
	// Helper functions
};
// Test main function
int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
// Test cases
TEST_F(MessageDecoderTest, CaseDefaultMessage) {
	std::vector<unsigned int> buffer;
	buffer.push_back(0);
	buffer.push_back(240);
	buffer.push_back(15);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(22);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(57);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(4);
	buffer.push_back(0);
	buffer.push_back(83);
	decoder->DecodeSerialPortMessage(buffer);
	EXPECT_EQ(0, decoder->GetSoilMoistureValue());
	EXPECT_EQ(22, decoder->GetTemperatureValue());
	EXPECT_EQ(57, decoder->GetHumidityValue());
	EXPECT_EQ(4, decoder->GetUVLevel());
}
