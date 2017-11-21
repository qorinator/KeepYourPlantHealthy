#include "ConfigureSerialPort.h"

#include <iostream>
#include <string.h>


ConfigureSerialPort::ConfigureSerialPort(struct termios& tty, 
						const int fileDescriptor, 
						const speed_t baudrate)
{	
	std::cout << "Configuring serial port for Arduino USB" << std::endl;
	memset(&tty, 0, sizeof tty);	
	if (GetFileDescriptorAttribute(tty, fileDescriptor) != 0)
		std::cout << "Unable to get attribut" << std::endl;
	if (!IsBaudrateSet(tty, baudrate))
		std::cout << "Unable to set m_baudrate" << std::endl;
	SetControlMode(tty);
	SetInputMode(tty);
	SetOutputMode(tty);
	SetLocalMode(tty);
	SetControlCharacters(tty);		
	if (!IsAttributeSet(tty, fileDescriptor))
		std::cout << "Unable to set attribute" << std::endl;
}

ConfigureSerialPort::~ConfigureSerialPort()
{
	std::cout << "Configuration is a success, destroy object" << std::endl;
}


int ConfigureSerialPort::GetFileDescriptorAttribute(struct termios& tty, const int fileDescriptor)
{
	return tcgetattr(fileDescriptor, &tty);
}

bool ConfigureSerialPort::IsBaudrateSet(struct termios& tty, const speed_t baudrate)
{
	return (IsInputBaudrateSet(tty, baudrate) && IsOutputBaudrateSet(tty, baudrate));
}

bool ConfigureSerialPort::IsInputBaudrateSet(struct termios& tty, const speed_t baudrate)
{
	return (cfsetispeed(&tty, baudrate) == 0);
}

bool ConfigureSerialPort::IsOutputBaudrateSet(struct termios& tty, const speed_t baudrate)
{
	return (cfsetospeed(&tty, baudrate) == 0);
}

void ConfigureSerialPort::SetControlMode(struct termios& tty)
{
	tty.c_cflag &= ~(CSIZE | PARENB);
	tty.c_cflag |= CS8;	
	tty.c_cflag |= (CLOCAL | CREAD);
}

void ConfigureSerialPort::SetInputMode(struct termios& tty)
{
	tty.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK 
					| INPCK | ISTRIP | IXON);	
}

void ConfigureSerialPort::SetOutputMode(struct termios& tty)
{
	tty.c_oflag &= ~OPOST;
}

void ConfigureSerialPort::SetLocalMode(struct termios& tty)
{
	tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
}

void ConfigureSerialPort::SetControlCharacters(struct termios& tty)
{
	tty.c_cc[VMIN]  = 1;
	tty.c_cc[VTIME] = 0;
}

bool ConfigureSerialPort::IsAttributeSet(struct termios& tty, const int fileDescriptor)
{
	return (tcsetattr(fileDescriptor, TCSAFLUSH, &tty) == 0);
}