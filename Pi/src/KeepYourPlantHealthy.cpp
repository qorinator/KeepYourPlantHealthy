#include <iostream>
#include <unistd.h>
#include "SerialPort.h"
#include "MessageDecoder.h"

int main(int argc, char *argv[])
{
	SerialPort arduinoUSB("/dev/ttyACM0", B115200);
	std::vector<unsigned int> rxBuffer;
	MessageDecoder decoder;
	arduinoUSB.SendDataRequest();
	while (1)
	{
		if (arduinoUSB.IsMessageReceived())
		{		
			rxBuffer = arduinoUSB.ReadRXBuffer();
			// decoder.DecodeSerialPortMessage(rxBuffer);
		}
	}
	return 0;	
}
