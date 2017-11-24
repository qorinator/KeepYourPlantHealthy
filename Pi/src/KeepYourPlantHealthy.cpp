#include <iostream>
#include <unistd.h>
#include <vector>
#include "SerialPort.h"
#include "MessageDecoder.h"
#include "ProtocolUnwrapper.h"
#include "SerialDataHandler.h"

int main(int argc, char *argv[])
{
	SerialPort arduinoUSB("/dev/ttyACM0", B115200);
	std::vector<unsigned int> rxBuffer;
	std::vector<Package> packages;
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
	 		packages = unwrapper->GetPackages();
	 		if(!packages.empty()) {	 			 		
	 			arduinoUSB.FlushRXBuffer();
	 			send = true;
	 		}
	 		delete unwrapper;
	 		unwrapper = nullptr;	 		
	 	}
	 	sleep(2);
	 }
	return 0;	
}
