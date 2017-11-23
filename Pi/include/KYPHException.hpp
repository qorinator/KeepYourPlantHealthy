#ifndef KYPHEXCEPTION_H
#define KYPHEXCEPTION_H

#include <exception>
#include <iostream>
#include <string>
#include <errno.h>

class OpenFileFailure : public std::exception 
{
public:
	char const* msg() const throw() {
		return "open";
	}
};

class ConfigureTerminalFailure : public std::exception 
{
public:
	ConfigureTerminalFailure(std::string msg)
		: _msg(msg)
	{}
	char const* msg() const throw() {
		return _msg.c_str();
	}
private:
	std::string _msg;
};

#endif // KYPHEXCEPTION_H