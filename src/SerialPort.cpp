#include "SerialPort.h"
#include "ConfigureSerialPort.h"
#include "KYPHException.hpp"

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
// #include <errno.h>


// Serial Port interrutpt handler
bool SerialPort::m_messageReceived = false;
void SerialPort::SerialPortSignalHandler(int status) {	 
	m_messageReceived = true;
}

// Public function
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

SerialPort::~SerialPort() {	
	ClosePort();
	std::cout << "Port is closed" << std::endl;
}

std::vector<unsigned int> SerialPort::ReadRXBuffer() {
	char buf[30] = { 0 };
	int n = read(m_fileDescriptor, buf, sizeof buf);
	std::cout << "===============================" << std::endl; 
	std::cout << "Received " << n << " bytes"  << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << (unsigned int)buf[i] << " ";
		m_rxBuffer.push_back(buf[i]);
	}
	std::cout << std::endl;
	std::vector<unsigned int> temp = m_rxBuffer;
	m_rxBuffer.clear();
	return temp;
}

void SerialPort::SendDataRequest() {
	int buffer[11] = { 	0x00, 0xF0, 0x0F,
						0x00, 0x53, 0x54, 0x41, 0x52, 0x54,
						0x00, 0x8E };
	write(m_fileDescriptor, buffer, sizeof buffer);
}

bool SerialPort::IsMessageReceived() {
	bool message = m_messageReceived;
	m_messageReceived = false;
	return message;
}

// Private function

void SerialPort::ClosePort() {
	close(m_fileDescriptor);
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