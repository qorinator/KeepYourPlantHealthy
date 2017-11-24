#ifndef PROTOCOLUNWRAPPER_H
#define PROTOCOLUNWRAPPER_H

#include <vector>
#include <string>

class ProtocolUnwrapper
{	
public:
	ProtocolUnwrapper(std::vector<unsigned int> const& rxBuffer);
	~ProtocolUnwrapper();
	bool IsMessageComplete();
private:
	void UnwrapMessage(std::vector<unsigned int> const& rxBuffer);
	void FindStartOfMessage(std::vector<unsigned int> const& rxBuffer);
	int GetNumberOfPackages(std::vector<unsigned int> const& rxBuffer);
	void GetMessageLength(std::vector<unsigned int> const& rxBuffer);
	void GetTotalPackagesLength(std::vector<unsigned int> const& rxBuffer, int const& numberOfPackages);
	int GetPackageDataLength(std::vector<unsigned int> const& rxBuffer, int const& index);
	void GetChecksumDataLength();
	bool IsNotFragmented(size_t const& length);
	bool IsChecksumOK(std::vector<unsigned int> const& rxBuffer);
private:
	bool _startMessagePackageFound;
	bool _messageIsComplete;	
	int _startIndex;
	unsigned int _expectedMessageLength;
	static const int _minimumLengthPerPackage = 4;
	static const int _lengthOfStartMessagePackage = 4;
	static const int _lengthOfChecksumPackage = 2;
	static const int _lengthOfDataHeader = 3;
	static const int _relativeIndexOfDataLength = 2;
};

#endif // PROTOCOLUNWRAPPER_H