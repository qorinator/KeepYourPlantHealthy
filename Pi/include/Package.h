#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <vector>

class Package 
{
public:
	Package();
	void SetID(unsigned int const& id);
	void SetLength(unsigned int const& length);
	void SetData(unsigned int const& data);
	unsigned int GetID() const;
	unsigned int GetLength() const;
	std::vector<unsigned int> GetData() const;
	void PrintPackage() const;
private: 
	unsigned int _id;
	unsigned int _length;
	std::vector<unsigned int> _data;
};

#endif // PACKAGE_H