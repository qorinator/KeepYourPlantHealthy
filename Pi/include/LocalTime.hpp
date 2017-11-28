#ifndef LOCALTIME_HPP
#define LOCALTIME_HPP

#include <string>
#include <iostream>

class LocalTime 
{
public:
	LocalTime();
	~LocalTime();
	std::string Get();
private:	
	std::string _time;
};

inline LocalTime::LocalTime() {
	time_t rawtime;	
	time(&rawtime);
	struct tm* timeinfo;
	timeinfo = localtime(&rawtime);
	char buffer[80];	
	strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",timeinfo);
	_time = std::string(buffer);
}

inline LocalTime::~LocalTime() {}

inline std::string LocalTime::Get() {
	return _time;
}

#endif // LOCALTIME_HPP


