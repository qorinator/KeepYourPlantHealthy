#include "SerialReadHandler.h"

SerialReadHandler::SerialReadHandler()
	: _dataRequestStatus(false)
	, _dataRequestMessageIsFound(false)
	, _packageComplete(false)
{}

bool SerialReadHandler::IsDataRequested() const {	
	return _dataRequestStatus;
}

void SerialReadHandler::AppendData(byte const& inChar) {
	_data.push_back(inChar);
}

void SerialReadHandler::CheckForDataRequest() {
	FindDataRequestMessage();
	if (_dataRequestMessageIsFound){		
		WaitForMessageToBeCompleted();
		if (_packageComplete) {
			if (IsCheckSumOK()) {
				_dataRequestStatus = true;	
				FlushMessageBuffer();				
			}
		}
	}
}

void SerialReadHandler::FlushMessageBuffer() {
	_data.clear();
}

void SerialReadHandler::FindDataRequestMessage() {
	for (size_t i = 0; i < _data.size(); i++){
		if ((_data[i] == 0x00) && (_data[i + 1] == 0xF0) && (_data[i + 2] == 0x0E)) {			
			_startingIndex = i;
			_dataRequestMessageIsFound = true;
		}		
	}
}

void SerialReadHandler::WaitForMessageToBeCompleted() {	
	if (HasNumberOfPackageArrived()) {
		int numberOfPackage = _data[_startingIndex + 3];
		int messageLength = 4;
		messageLength = messageLength + numberOfPackage + 2;
		if ((_data.size()) == (_startingIndex + messageLength)) {
			_packageComplete = true;
		}
	}
	
}

bool SerialReadHandler::HasNumberOfPackageArrived() {
	return (_data.size()) > (_startingIndex + 3);
}

bool SerialReadHandler::IsCheckSumOK() {
	if (!_data.empty()) {
		byte checksum = _data.back();
		_data.pop_back();

		byte sum = 0;
		for (size_t i = _startingIndex; i < _data.size(); i++) {
			sum = (sum + _data[i]) & 0xFF;
		}	
		return (sum && checksum);
	}		
	return false;
}

void SerialReadHandler::RequestCompleted() {
	_dataRequestStatus = false;
	_dataRequestMessageIsFound = false;
	_packageComplete = false;
}