#ifndef SERIALDATAHANDLER_H
#define SERIALDATAHANDLER_H

#include <vector>
#include <string>
class SerialDataHandler
{
public:
	SerialDataHandler(std::vector<unsigned int> const& rxBuffer);
	~SerialDataHandler();
	std::vector<int> GetDataIndex() const;
	bool IsMessageReady() const;
private:
	bool GetCompleteMessage(std::vector<unsigned int> const& rxBuffer);
	bool FindStartOfMessage(std::vector<unsigned int> const& rxBuffer);
	bool GetCompleteMessageLength(std::vector<unsigned int> const& rxBuffer);
	int GetNumberOfPackages(std::vector<unsigned int> const& rxBuffer);	
	void GetLengthOfTotalPackage(std::vector<unsigned int> const& rxBuffer, int const& numberOfPackages);
	int GetLengthOfPackageData(std::vector<unsigned int> const& rxBuffer, int const& index);
	void GetChecksumDataLength();
	bool IsNotFragmented(size_t const& length);
	bool IsChecksumOK(std::vector<unsigned int> const& rxBuffer);
private:
	int _startIndex;
	unsigned int _expectedMessageLength;
	std::vector<int> _dataIndex;
	bool _messageReady;
	static const int _minimumLengthPerPackage = 4;
	static const int _lengthOfStartMessagePackage = 4;
	static const int _lengthOfChecksumPackage = 2;
	static const int _lengthOfDataHeader = 3;
	static const int _relativeIndexOfDataLength = 2;
};

#endif // SERIALDATAHANDLER_H