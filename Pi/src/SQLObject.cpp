#include "SQLObject.h"
#include <iostream>

SQLObject::~SQLObject() {}

SQLObject::SQLObject(std::string const& name)
	: _name(name)
	, _date()
	, _average()
	, _minimum()
	, _maximum()
{}

void SQLObject::InitializeValues(std::string const& date, float const& value) {
	SetDate(date);
	SetAverage(0);
	InitializeMinimum(value);
	InitializeMaximum(value);	
}

void SQLObject::SetValues(float const& average, float const& value) {
	SetAverage(average);
	SetMinimum(value);
	SetMaximum(value);	
}

std::string SQLObject::GetName() const {
	return _name;
}
std::string SQLObject::GetDate() const {
	return _date;
}
float SQLObject::GetAverage() const {
	return _average;
}
float SQLObject::GetMinimum() const {
	return _minimum;
}
float SQLObject::GetMaximum() const {
	return _maximum;
}

void SQLObject::SetDate(std::string const& date) {
	_date = date;
}
void SQLObject::SetAverage(float const& average) {
	_average = average;
}
void SQLObject::InitializeMinimum(float const& value) {
	_minimum = value;
}
void SQLObject::InitializeMaximum(float const& value) {
	_maximum = value;
}
void SQLObject::SetMinimum(float const& value) {	
	_minimum = (value < _minimum) ? value : _minimum;	
}
void SQLObject::SetMaximum(float const& value) {
	_maximum = (value > _maximum) ? value : _maximum;
}