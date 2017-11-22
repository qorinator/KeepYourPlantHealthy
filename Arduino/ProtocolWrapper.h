#ifndef _PROTOCOLWRAPPER_h
#define _PROTOCOLWRAPPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Package.h"
#include <StandardCplusplus\StandardCplusplus.h>
#include <StandardCplusplus\vector>

class ProtocolWrapper
{
public:
	ProtocolWrapper(std::vector<Package> const& packages);
	std::vector<byte> GetWrappedPackages() const;
private:
	void WrapPackages(std::vector<Package> const& packages);
	void AddStartMessage(byte packagesSize);
	void AppendPackage(std::vector<Package> const& packages);
	byte CalculateChecksum();
	void AddChecksum();
private:
	std::vector<byte> _wrappedPackage;

};

#endif // _PROTOCOLWRAPPER_h

