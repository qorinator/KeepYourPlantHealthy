#ifndef SQLOBJECT_H
#define SQLOBJECT_H

#include <string>

class SQLObject
{
public:
	SQLObject(std::string const& name);
	~SQLObject();

	void InitializeValues(std::string const& date, float const& value);
	void SetValues(float const& average, float const& value);
	std::string GetDate() const;
	std::string GetName() const;
	float GetAverage() const;
	float GetMinimum() const;
	float GetMaximum() const;
private:
	void InitializeMinimum(float const& value);
	void InitializeMaximum(float const& value);
	void SetDate(std::string const& date);
	void SetAverage(float const& value);
	void SetMinimum(float const& value);
	void SetMaximum(float const& value);
	
private:
	std::string _name;
	std::string _date;
	float _average;
	float _minimum;
	float _maximum;	
};

#endif // SQLOBJECT_H