#include "ProtocolUnwrapper.h"

#include <iostream>

ProtocolUnwrapper::~ProtocolUnwrapper() {}

ProtocolUnwrapper::ProtocolUnwrapper(std::vector<unsigned int> const& rxBuffer)
	: _startMessagePackageFound(false)
	, _messageIsComplete(false)
	, _startIndex(0)
	, _expectedMessageLength(3)
{
	UnwrapMessage(rxBuffer);
}

void ProtocolUnwrapper::UnwrapMessage(std::vector<unsigned int> const& rxBuffer) {
	FindStartOfMessage(rxBuffer);
	if(_startMessagePackageFound)
		GetMessageLength(rxBuffer);	
	if(_messageIsComplete){
		std::cout << "rxBuffer size " << rxBuffer.size() << " bytes"  << std::endl;
		for (auto it = rxBuffer.begin(); it != rxBuffer.end(); ++it)
			std::cout << (unsigned int)(*it) << " ";
		std::cout << std::endl;
	}
}

void ProtocolUnwrapper::FindStartOfMessage(std::vector<unsigned int> const& rxBuffer) {
	size_t bufferLength = rxBuffer.size();
	if(IsNotFragmented(bufferLength)) {
		for (size_t i = 0; i < bufferLength; i++){
			if ((rxBuffer[i] == 0x00) && (rxBuffer[i + 1] == 0xF0) && (rxBuffer[i + 2] == 0x0F)) {
				_startMessagePackageFound = true;
				_startIndex = i;
				_expectedMessageLength++;
			}	
		}	
	}	
}

void ProtocolUnwrapper::GetMessageLength(std::vector<unsigned int> const& rxBuffer) {
	int numberOfPackages = GetNumberOfPackages(rxBuffer);
	if(numberOfPackages	> 0) {
		GetTotalPackagesLength(rxBuffer, numberOfPackages);
		if(rxBuffer.size() == _expectedMessageLength)
			_messageIsComplete = IsChecksumOK(rxBuffer);
	}	
}

int ProtocolUnwrapper::GetNumberOfPackages(std::vector<unsigned int> const& rxBuffer) {
	int numberOfPackages = 0;
	if(IsNotFragmented(rxBuffer.size()))
		numberOfPackages = rxBuffer[_startIndex + 3];
	return numberOfPackages;
}

void ProtocolUnwrapper::GetTotalPackagesLength(std::vector<unsigned int> const& rxBuffer, int const& numberOfPackages) {
	unsigned int startDataIndex = _startIndex + _lengthOfStartMessagePackage;
	bool IsBreak = false;	
	_expectedMessageLength += (numberOfPackages * _minimumLengthPerPackage);

	for(int i = 0; i < numberOfPackages; i++) {
		if(IsNotFragmented(rxBuffer.size())) {				
			int length = GetPackageDataLength(rxBuffer, startDataIndex);
			startDataIndex += length;
			_expectedMessageLength = startDataIndex + _minimumLengthPerPackage;
		}
		else {			
			IsBreak	= true;
			break;
		}
	}
	if(!IsBreak)
		GetChecksumDataLength();
}

void ProtocolUnwrapper::GetChecksumDataLength() {
	_expectedMessageLength -= _minimumLengthPerPackage; 
	_expectedMessageLength += _lengthOfChecksumPackage;
}

bool ProtocolUnwrapper::IsNotFragmented(size_t const& length) {
	return	(length >= _expectedMessageLength);
}

int ProtocolUnwrapper::GetPackageDataLength(std::vector<unsigned int> const& rxBuffer, int const& index) {
	return rxBuffer[index + _relativeIndexOfDataLength] + _lengthOfDataHeader;
}

bool ProtocolUnwrapper::IsMessageComplete() {
	return _messageIsComplete;
}

bool ProtocolUnwrapper::IsChecksumOK(std::vector<unsigned int> const& rxBuffer) {
	unsigned int checksum = 0;
	int lastDataIndex = _expectedMessageLength - 1;
	for(int i = _startIndex; i < lastDataIndex; i++)
		checksum = (checksum + rxBuffer[i]) & 0xFF;
	return (checksum == rxBuffer[lastDataIndex]);
}