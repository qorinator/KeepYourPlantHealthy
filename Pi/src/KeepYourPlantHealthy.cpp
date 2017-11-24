#include <iostream>
#include <unistd.h>
#include "SerialPort.h"
#include "MessageDecoder.h"
#include "ProtocolUnwrapper.h"

int main(int argc, char *argv[])
{
	SerialPort arduinoUSB("/dev/ttyACM0", B115200);
	std::vector<unsigned int> rxBuffer;
	MessageDecoder decoder;
	sleep(3);
	bool send = true;
	while (1) {
		if(send) {
			std::cout << "===============================" << std::endl; 
			arduinoUSB.SendDataRequest();
			send = false;
		}

		if (arduinoUSB.IsMessageReceived())
	 	{		 		
	 		rxBuffer = arduinoUSB.ReadRXBuffer();
	 		
	 		ProtocolUnwrapper* unwrapper = new ProtocolUnwrapper(rxBuffer);
	 		send = unwrapper->IsMessageComplete();
	 		if(send)	 			
	 			arduinoUSB.FlushRXBuffer();
	 		delete unwrapper;
	 		
	 		// decoder.DecodeSerialPortMessage(rxBuffer);
	 	}
	 	sleep(2);
	 }
	return 0;	
}
