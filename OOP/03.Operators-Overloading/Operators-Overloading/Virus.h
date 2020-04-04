#pragma once
#include <iostream>
class Virus
{
public: 
	Virus(double severity = 0, const char* name = "");
	Virus(const Virus& other);
	Virus& operator=(const Virus& other);
	~Virus();

	const char* getName() const; //const char* !!!!
	double getSeverity() const;

	void setName(const char* name);
	void setSeverity(double severity);

	bool operator<(const Virus& other) const;
	bool operator<=(const Virus& other) const;
	bool operator>(const Virus& other) const;
	bool operator>=(const Virus& other) const;

private:
	char* name;
	double severity;
	void copy(const Virus& other);
};

