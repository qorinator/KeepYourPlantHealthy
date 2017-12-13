#ifndef _PACKAGE_h
#define _PACKAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <StandardCplusplus\StandardCplusplus.h>
#include <StandardCplusplus\vector>

class Package
{
public:
	Package();
	void SetID(byte const& id);
	void SetLength(byte const& length);
	void SetData(std::vector<byte> const& data);
	byte GetID() const;
	byte GetLength() const;
	std::vector<byte> GetData() const;
	void PrintPackage() const;
private: 
	byte _id;
	byte _length;
	std::vector<byte> _sensorValue;
};

#endif

