#ifndef TIME_HPP
#define TIME_HPP

class Time {
public:
	Time();
	~Time();
private:	
	std::string _time;
};

inline Time::Time() {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
	_time = std::string(buffer);
  	std::cout << _time << std::endl;
}

#endif // TIME_HPP


