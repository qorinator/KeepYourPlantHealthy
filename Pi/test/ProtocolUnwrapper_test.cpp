#include "ProtocolUnwrapper.h"
#include "gtest/gtest.h"

class ProtocolUnwrapperTest : public ::testing::Test {
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

TEST_F(ProtocolUnwrapperTest, Case3Packages) {
	size_t packageSize = 3;
	ProtocolUnwrapper unwrapper(buffer);	
	ASSERT_EQ(unwrapper.GetPackages().size(), packageSize);
	ASSERT_EQ(unwrapper.GetPackages()[0].GetID(), (unsigned int)0x01);
	ASSERT_EQ(unwrapper.GetPackages()[0].GetLength(), (unsigned int)0x02);
	ASSERT_EQ(unwrapper.GetPackages()[0].GetData()[0], (unsigned int)0x02);
	ASSERT_EQ(unwrapper.GetPackages()[0].GetData()[1],(unsigned int) 0x58);
}

TEST_F(ProtocolUnwrapperTest, CaseNoPackage) {
	buffer.clear();
	ProtocolUnwrapper unwrapper(buffer);	
	ASSERT_TRUE(unwrapper.GetPackages().empty());	
}

TEST_F(ProtocolUnwrapperTest, CaseIncompletePackage) {
	buffer.resize(buffer.size() - 4);
	ProtocolUnwrapper unwrapper(buffer);	
	ASSERT_TRUE(unwrapper.GetPackages().empty());	
}