#include "SerialPortMessageDecoder.h"
#include "gtest/gtest.h"

class SerialPortMessageDecoderTest : public ::testing::Test
{
protected:
	// Test Object
	SerialPortMessageDecoder* decoder;	
	// Before every test
	virtual void SetUp()
	{
		decoder = new SerialPortMessageDecoder();
	}
	// After every test
	virtual void TearDown()
	{
		delete decoder;
		decoder = nullptr;
	}

	// Helper functions
};

// Test cases

// Test main function
int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}