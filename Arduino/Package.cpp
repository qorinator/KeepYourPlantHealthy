#include "Package.h"

Package::Package()
	: _id()
	, _length()
	, _data()
{}

void Package::SetID(byte const& id) {
	_id = id;
}
void Package::SetLength(byte const& length) {
	_length = length;
}
void Package::SetData(std::vector<byte> const& data) {
	_data = data;
}
byte Package::GetID() const {
	return _id;
}
byte Package::GetLength() const {
	return _length;
}
std::vector<byte> Package::GetData() const {
	return _data;
}

void Package::PrintPackage() const {
	Serial.print("ID : "); 
	Serial.print(_id);
	Serial.print(" length: ");
	Serial.print(_length);
	Serial.print(" -> ");
	for (auto it = _data.begin(); it != _data.end(); ++it) {
		Serial.print(*it);
		Serial.print(" ");
	}
	Serial.print("\n");
}