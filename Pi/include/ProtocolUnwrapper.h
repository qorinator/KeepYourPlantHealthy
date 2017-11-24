#ifndef PROTOCOLUNWRAPPER_H
#define PROTOCOLUNWRAPPER_H

#include "Package.h"
#include "SerialDataHandler.h"

#include <vector>
#include <string>

class ProtocolUnwrapper
{	
public:
	ProtocolUnwrapper(std::vector<unsigned int> const& rxBuffer);
	~ProtocolUnwrapper();
	std::vector<Package> GetPackages() const;
private:		
	void UnwrapMessage(std::vector<unsigned int> const& rxBuffer, std::vector<int> const& dataIndex);
	void RepackageMessage(std::vector<unsigned int> const& rxBuffer, int const& index);
	int GetLengthOfPackageData(std::vector<unsigned int> const& rxBuffer, int const& index);
private:	
	std::vector<Package> _packages;		
	static const int _lengthOfDataHeader = 3;
	static const int _relativeIndexOfDataLength = 2;
};

#endif // PROTOCOLUNWRAPPER_H