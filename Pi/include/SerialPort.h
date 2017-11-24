#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>
#include <termios.h>
#include <queue>
#include <sys/signal.h>

class SerialPort
{	
private:	
	static bool m_messageReceived;	
	static void SerialPortSignalHandler(int status);
public:
	SerialPort(const char* filePath, int baudrate);		
	~SerialPort();
	std::vector<unsigned int> ReadRXBuffer();	
	void SendDataRequest();
	bool IsMessageReceived();
	void FlushRXBuffer();
private:
	void OpenPort(const char* filePath);	
	void ClosePort();
	bool IsPortOpen();	
	void ConfigurePortInterrupt();
private:	
	int	_fileDescriptor;
	struct termios				_tty;
	struct sigaction			_saio;
	speed_t						_baudrate;
	std::vector<unsigned int>	_rxBuffer;	
};

#endif // SERIALPORT_H




