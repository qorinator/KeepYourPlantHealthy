#include "SerialPort.h"
#include "SPConfigure.h"
#include "KYPHException.hpp"

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

bool SerialPort::m_messageReceived = false;
void SerialPort::SerialPortSignalHandler(int status) {
	m_messageReceived = true;
}

SerialPort::SerialPort(const char* filePath, int baudrate)
	: m_baudrate(baudrate) 
{
	try{
		OpenPort(filePath);
		ConfigurePortInterrupt();
		ConfigureSerialPort(m_tty, m_fileDescriptor, m_baudrate);
	}
	catch(OpenFileFailure& e){
		perror(e.msg());
		exit(EXIT_FAILURE);
	}
}

void SerialPort::OpenPort(const char* filePath) {	
	m_fileDescriptor = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	if(!IsPortOpen())
		throw OpenFileFailure();
}

bool SerialPort::IsPortOpen() {
	return (m_fileDescriptor != -1);
}

void SerialPort::ConfigurePortInterrupt() {
	m_saio.sa_handler = SerialPortSignalHandler;
	m_saio.sa_flags = 0;
	m_saio.sa_restorer = NULL;
	sigaction(SIGIO, &m_saio, NULL);	
	fcntl(m_fileDescriptor, F_SETFL, FNDELAY | FASYNC);
	fcntl(m_fileDescriptor, F_SETOWN, getpid());
	fcntl(m_fileDescriptor, F_SETFL, O_ASYNC); 
}

void SerialPort::SendDataRequest() {	
	uint8_t buffer[6] = {0, 240, 14, 0, 0, 254};
	write(m_fileDescriptor, buffer, sizeof buffer);
}

bool SerialPort::IsMessageReceived() {
	bool message = m_messageReceived;
	m_messageReceived = false;
	return message;
}

std::vector<unsigned int> SerialPort::ReadRXBuffer() {
	char buf[30] = { 0 };
	int n = read(m_fileDescriptor, buf, sizeof buf);
	for (int i = 0; i < n; i++)
		m_rxBuffer.push_back(buf[i]);
	return m_rxBuffer;
}

void SerialPort::FlushRXBuffer() {
	m_rxBuffer.clear();
}

SerialPort::~SerialPort() {	
	ClosePort();
}

void SerialPort::ClosePort() {
	close(m_fileDescriptor);
}
