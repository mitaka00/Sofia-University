#include "Virus.h"
#include<iostream>

Virus::Virus(double severity,const char* name)
{
	setName(name);
	setSeverity(severity);
}

Virus::Virus(const Virus& other)
{
	copy(other);
}

Virus& Virus::operator=(const Virus& other)
{
	if (this != &other) {
		delete[] name;
		copy(other);
	}
	return *this;
}

Virus::~Virus()
{
	delete[] name;
}

const char* Virus::getName() const
{
	return name;
}

double Virus::getSeverity() const
{
	return severity;
}

void Virus::setName(const char* name)
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}

void Virus::setSeverity(double severity)
{
	this->severity = severity;
}

bool Virus::operator<(const Virus& other) const
{
	return severity < other.severity;
}

bool Virus::operator<=(const Virus& other) const
{
	return !(*this > other);
}

bool Virus::operator>(const Virus& other) const
{
	return severity > other.severity;
}

bool Virus::operator>=(const Virus& other) const
{
	return !(*this < other);
}

void Virus::copy(const Virus& other)
{
	setName(other.name);
	setSeverity(other.severity);
}
