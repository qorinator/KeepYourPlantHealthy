#include <iostream>
#include <unistd.h>
#include "SerialPort.h"
#include "SerialPortMessageDecoder.h"

int main(int argc, char *argv[])
{
	SerialPort arduinoUSB("/dev/ttyACM0", B115200);
	std::vector<unsigned int> rxBuffer;
	SerialPortMessageDecoder decoder;
	// int i = 0;
	while (1)
	{
		// if(i < 10)
		// {
		// 	arduinoUSB.SendDataRequest();						
		// }
		if (arduinoUSB.IsMessageReceived())
		{		
			rxBuffer = arduinoUSB.ReadRXBuffer();
			decoder.DecodeSerialPortMessage(rxBuffer);
			// i++;
		}
	}
	return 0;	
}
