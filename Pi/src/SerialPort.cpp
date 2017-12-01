#include "SerialPort.h"
#include "SPConfigure.h"
#include "KYPHException.hpp"

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

bool SerialPort::m_messageReceived = false;
void SerialPort::SerialPortSignalHandler(int status) {
	m_messageReceived = true;
}

SerialPort::SerialPort(const char* filePath, int baudrate)
	: _baudrate(baudrate) 
{
	try{
		OpenPort(filePath);
		ConfigurePortInterrupt();
		ConfigureSerialPort(_tty, _fileDescriptor, _baudrate);
	}
	catch(ConfigureTerminalFailure& e){
		perror(e.msg());
		exit(EXIT_FAILURE);
	}
}

void SerialPort::OpenPort(const char* filePath) {	
	_fileDescriptor = open(filePath, O_RDWR | O_NOCTTY | O_NDELAY);
	if(!IsPortOpen())
		throw ConfigureTerminalFailure(filePath);
}

bool SerialPort::IsPortOpen() {
	return (_fileDescriptor != -1);
}

void SerialPort::ConfigurePortInterrupt() {
	_saio.sa_handler = SerialPortSignalHandler;
	_saio.sa_flags = 0;
	_saio.sa_restorer = NULL;
	sigaction(SIGIO, &_saio, NULL);	
	fcntl(_fileDescriptor, F_SETFL, FNDELAY | FASYNC);
	fcntl(_fileDescriptor, F_SETOWN, getpid());
	fcntl(_fileDescriptor, F_SETFL, O_ASYNC); 
}

void SerialPort::SendDataRequest() {	
	uint8_t buffer[6] = {0, 240, 14, 0, 0, 254};
	write(_fileDescriptor, buffer, sizeof buffer);
}

bool SerialPort::IsMessageReceived() {
	bool message = m_messageReceived;
	m_messageReceived = false;
	return message;
}

std::vector<unsigned int> SerialPort::ReadRXBuffer() {
	char buf[30] = { 0 };
	int n = read(_fileDescriptor, buf, sizeof buf);
	for (int i = 0; i < n; i++)
		_rxBuffer.push_back(buf[i]);
	return _rxBuffer;
}

void SerialPort::FlushRXBuffer() {
	_rxBuffer.clear();
}

SerialPort::~SerialPort() {	
	ClosePort();
}

void SerialPort::ClosePort() {
	close(_fileDescriptor);
}
