#ifndef CONFIGURESERIALPORT_H
#define CONFIGURESERIALPORT_H

#include <termios.h>

class ConfigureSerialPort
{
public:
	ConfigureSerialPort(struct termios& tty, 
						const int fileDescriptor, 
						const speed_t baudrate);
	~ConfigureSerialPort();
private:
	void GetFileDescriptorAttribute(struct termios& tty, const int fileDescriptor);
	void SetInputBaudrate(struct termios& tty, const speed_t baudrate);
	void SetOutputBaudrate(struct termios& tty, const speed_t baudrate);
	void ConfigureMode(struct termios& tty);
	void SetControlMode(struct termios& tty);
	void SetInputMode(struct termios& tty);
	void SetOutputMode(struct termios& tty);
	void SetLocalMode(struct termios& tty);
	void SetControlCharacters(struct termios& tty);
	void SetAttribute(struct termios& tty, const int fileDescriptor);
};

#endif // CONFIGURESERIALPORT_H