#include "Package.h"

#include <iostream>

Package::Package()
	: _id()
	, _length()
	, _data()
{}

void Package::SetID(unsigned int const& id) {
	_id = id;
}
void Package::SetLength(unsigned int const& length) {
	_length = length;
}
void Package::SetData(unsigned int const& data) {
	_data.push_back(data);
}
unsigned int Package::GetID() const {
	return _id;
}
unsigned int Package::GetLength() const {
	return _length;
}
std::vector<unsigned int> Package::GetData() const {
	return _data;
}

void Package::PrintPackage() const {
	std::cout << ("ID : ") << _id << std::endl;
	std::cout << ("Length : ") << _length << std::endl;
	std::cout << ("Data ");
	for (auto it = _data.begin(); it != _data.end(); ++it) {
		std::cout << (*it) << (" ");
	}
	std::cout << std::endl;
}