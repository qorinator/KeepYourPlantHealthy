#include "SerialDataHandler.h"
#include <iostream>

SerialDataHandler::~SerialDataHandler() {}
SerialDataHandler::SerialDataHandler(std::vector<unsigned int> const& rxBuffer)
	: _startIndex(0)
	, _expectedMessageLength(3)	
	, _dataIndex()
	, _messageReady(false)
{
	_messageReady = GetCompleteMessage(rxBuffer);
}


bool SerialDataHandler::GetCompleteMessage(std::vector<unsigned int> const& rxBuffer) {	
	if(FindStartOfMessage(rxBuffer))
		return GetCompleteMessageLength(rxBuffer);
	return false;
}

bool SerialDataHandler::FindStartOfMessage(std::vector<unsigned int> const& rxBuffer) {
	size_t bufferLength = rxBuffer.size();
	if(IsNotFragmented(bufferLength)) {
		for (size_t i = 0; i < bufferLength; i++){
			if ((rxBuffer[i] == 0x00) && (rxBuffer[i + 1] == 0xF0) && (rxBuffer[i + 2] == 0x0F)) {				
				_startIndex = i;
				_expectedMessageLength++;
				return true;
			}
		}	
	}
	return	false;
}

bool SerialDataHandler::GetCompleteMessageLength(std::vector<unsigned int> const& rxBuffer) {
	int numberOfPackages = GetNumberOfPackages(rxBuffer);
	GetLengthOfTotalPackage(rxBuffer, numberOfPackages);
	if(rxBuffer.size() == _expectedMessageLength)
		return IsChecksumOK(rxBuffer);
	return false;
}

int SerialDataHandler::GetNumberOfPackages(std::vector<unsigned int> const& rxBuffer) {
	if(IsNotFragmented(rxBuffer.size()))
		return rxBuffer[_startIndex + 3];
	return 0;
}

void SerialDataHandler::GetLengthOfTotalPackage(std::vector<unsigned int> const& rxBuffer, int const& numberOfPackages) {
	unsigned int startDataIndex = _startIndex + _lengthOfStartMessagePackage;
	bool IsBreak = false;	
	_expectedMessageLength += (numberOfPackages * _minimumLengthPerPackage);

	for(int i = 0; i < numberOfPackages; i++) {
		if(IsNotFragmented(rxBuffer.size())) {				
			int length = GetLengthOfPackageData(rxBuffer, startDataIndex);
			_dataIndex.push_back(startDataIndex);
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

int SerialDataHandler::GetLengthOfPackageData(std::vector<unsigned int> const& rxBuffer, int const& index) {
	return rxBuffer[index + _relativeIndexOfDataLength] + _lengthOfDataHeader;
}

void SerialDataHandler::GetChecksumDataLength() {
	_expectedMessageLength -= _minimumLengthPerPackage; 
	_expectedMessageLength += _lengthOfChecksumPackage;
}

bool SerialDataHandler::IsChecksumOK(std::vector<unsigned int> const& rxBuffer) {
	unsigned int checksum = 0;
	int lastDataIndex = _expectedMessageLength - 1;
	for(int i = _startIndex; i < lastDataIndex; i++)
		checksum = (checksum + rxBuffer[i]) & 0xFF;
	return (checksum == rxBuffer[lastDataIndex]);
}

bool SerialDataHandler::IsNotFragmented(size_t const& length) {
	return	(length >= _expectedMessageLength);
}

std::vector<int> SerialDataHandler::GetDataIndex() const {
	return _dataIndex;
}

bool SerialDataHandler::IsMessageReady() const {
	return _messageReady;
}