#ifndef _SERIAL_H_
#define _SERIAL_H_

#include<fstream>
#include<string>

class Serializer
{
public:
	Serializer(const std::string& fileName);
	Serializer& Put(int x);
	Serializer& Put(unsigned int x);
	Serializer& Put(long x);
	Serializer& Put(unsigned long x);
	Serializer& Put(double x);
	Serializer& Put(const std::string& fileName);
	Serializer& Put(bool x);

	Serializer& operator<<(int x);
	Serializer& operator<<(unsigned int x);
	Serializer& operator<<(long x);
	Serializer& operator<<(unsigned long x);
	Serializer& operator<<(double x);
	Serializer& operator<<(const std::string& fileName);
	Serializer& operator<<(bool x);

private:
	std::ofstream stream_;
};

class DeSerializer
{
public:
	DeSerializer(const std::string& fileName);
	DeSerializer& Get(int& x);
	DeSerializer& Get(unsigned int& x);
	DeSerializer& Get(long& x);
	DeSerializer& Get(unsigned long& x);
	DeSerializer& Get(double& x);
	DeSerializer& Get(std::string& fileName);
	DeSerializer& Get(bool& x);

	DeSerializer& operator>>(int& x);
	DeSerializer& operator>>(unsigned int& x);
	DeSerializer& operator>>(long& x);
	DeSerializer& operator>>(unsigned long& x);
	DeSerializer& operator>>(double& x);
	DeSerializer& operator>>(std::string& fileName);
	DeSerializer& operator>>(bool& x);

private:
	std::ifstream stream_;
};

class Serializable
{
public:
	virtual void Serialize(Serializer& out) const = 0;
	virtual void DeSerialize(DeSerializer& in) = 0;
};
#endif //_SERIAL_H_
