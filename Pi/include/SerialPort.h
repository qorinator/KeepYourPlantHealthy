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
private:
	void OpenPort(const char* filePath);	
	void ClosePort();
	bool IsPortOpen();	
	void ConfigurePortInterrupt();
private:	
	int							m_fileDescriptor;
	struct termios				m_tty;
	struct sigaction			m_saio;
	speed_t						m_baudrate;
	std::vector<unsigned int>	m_rxBuffer;	
};

#endif // SERIALPORT_H




