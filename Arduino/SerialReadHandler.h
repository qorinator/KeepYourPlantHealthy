#ifndef _SERIALREADHANDLER_h
#define _SERIALREADHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <StandardCplusplus\StandardCplusplus.h>
#include <StandardCplusplus\vector>

class SerialReadHandler
{
public:
	 SerialReadHandler();
	 bool IsDataRequested() const;
	 void AppendData(byte const& inChar);
	 void CheckForDataRequest();
	 void FlushMessageBuffer();
	 void RequestCompleted();
private:
	void FindDataRequestMessage();
	bool IsCheckSumOK();
	void WaitForMessageToBeCompleted();
	bool HasNumberOfPackageArrived();
private:
	bool _dataRequestStatus;
	bool _dataRequestMessageIsFound;
	bool _packageComplete;
	std::vector<byte> _data;
	int _startingIndex;
};


#endif // _SERIALREADHANDLER_h

