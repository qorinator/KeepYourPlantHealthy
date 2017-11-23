<<<<<<< HEAD:include/ConfigureSerialPort.h
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

=======
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
	int GetFileDescriptorAttribute(struct termios& tty, const int fileDescriptor);
	bool IsBaudrateSet(struct termios& tty, const speed_t baudrate);
	bool IsInputBaudrateSet(struct termios& tty, const speed_t baudrate);
	bool IsOutputBaudrateSet(struct termios& tty, const speed_t baudrate);
	void ConfigureMode(struct termios& tty);
	void SetControlMode(struct termios& tty);
	void SetInputMode(struct termios& tty);
	void SetOutputMode(struct termios& tty);
	void SetLocalMode(struct termios& tty);
	void SetControlCharacters(struct termios& tty);
	bool IsAttributeSet(struct termios& tty, const int fileDescriptor);
};

>>>>>>> 1ba89d320f2e8927a945ad56c129ce00a27a3754:Pi/include/ConfigureSerialPort.h
#endif // CONFIGURESERIALPORT_H