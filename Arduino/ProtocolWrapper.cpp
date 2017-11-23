#include "ProtocolWrapper.h"

ProtocolWrapper::ProtocolWrapper(std::vector<Package> const& packages)
	: _wrappedPackage()
{
	WrapPackages(packages);
}

void ProtocolWrapper::WrapPackages(std::vector<Package> const& packages) {
	InitializeMessage();
	AddStartMessage(packages.size());
	AppendPackage(packages);
	AddChecksum();
}
void ProtocolWrapper::InitializeMessage() {
	_wrappedPackage.clear();
}
void ProtocolWrapper::AddStartMessage(byte const& packagesSize) {
	_wrappedPackage.push_back(0x00);
	_wrappedPackage.push_back(0xF0);
	_wrappedPackage.push_back(0x0F);
	_wrappedPackage.push_back(packagesSize);
}
void ProtocolWrapper::AppendPackage(std::vector<Package> const& packages) {
	for (auto package = packages.begin(); package != packages.end(); ++package) {
		_wrappedPackage.push_back(0x00);
		_wrappedPackage.push_back(package->GetID());
		_wrappedPackage.push_back(package->GetLength());
		std::vector<byte> data = package->GetData();
		for (auto it = data.begin(); it != data.end(); ++it) 
			_wrappedPackage.push_back(*it);
	}
}
void ProtocolWrapper::AddChecksum() {
	_wrappedPackage.push_back(0x00);
	_wrappedPackage.push_back(CalculateChecksum());
}
byte ProtocolWrapper::CalculateChecksum() {
	byte checksum = 0;
	for (auto it = _wrappedPackage.begin(); it != _wrappedPackage.end(); ++it) {		
		checksum = (checksum + (*it)) & 0xFF;
	}
	return checksum;
}

std::vector<byte> ProtocolWrapper::GetWrappedPackages() const {
	return _wrappedPackage;
}
