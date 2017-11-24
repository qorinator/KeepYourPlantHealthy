#include "ProtocolUnwrapper.h"
#include <iostream>

ProtocolUnwrapper::~ProtocolUnwrapper() {}

ProtocolUnwrapper::ProtocolUnwrapper(std::vector<unsigned int> const& rxBuffer)
{
	SerialDataHandler* handler = new SerialDataHandler(rxBuffer);
	if(handler->IsMessageReady()) 
		UnwrapMessage(rxBuffer, handler->GetDataIndex());
	delete handler;
	handler = nullptr;
}

void ProtocolUnwrapper::UnwrapMessage(std::vector<unsigned int> const& rxBuffer, std::vector<int> const& dataIndex) {
	for(auto it = dataIndex.begin(); it != dataIndex.end(); ++it)
		RepackageMessage(rxBuffer, *it);	
}

void ProtocolUnwrapper::RepackageMessage(std::vector<unsigned int> const& rxBuffer, int const& index) {
	Package package; 
	int length = GetLengthOfPackageData(rxBuffer, index);	
	for(int i = 1; i < length; i++) {
		unsigned int data = rxBuffer[index + i];
		switch(i) {
			case 1:
				package.SetID(data);
				break;
			case 2:
				package.SetLength(data);
				break;
			default:
				package.SetData(data);
				break;
		}
	}	
	_packages.push_back(package);
}

int ProtocolUnwrapper::GetLengthOfPackageData(std::vector<unsigned int> const& rxBuffer, int const& index) {
	return rxBuffer[index + _relativeIndexOfDataLength] + _lengthOfDataHeader;
}

std::vector<Package> ProtocolUnwrapper::GetPackages() const {
	return _packages;
}
