#include "Destination.h"
#include <iostream>

using string = std::string;
Destination::Destination(const string name, int grade, const string comment, Date start, Date end) :
	name(name),
	grade(grade),
	comment(comment),
	start(start),
	end(end)
{}

Destination::Destination(const Destination & other)
{
	copy(other);
}

Destination& Destination::operator=(const Destination& other)
{
	if (&other != this) {
		copy(other);
	}

	return *this;
}

void Destination::serialize(std::ofstream& out) const
{
	//TODO 
}

void Destination::addImage(const string imageName)
{
	images.push_back(imageName);
}

void Destination::copy(const Destination& other)
{
	name = other.name;
	grade = other.grade;
	comment = other.comment;
	start = other.start;
	end = other.end;
	images = other.images;
}

std::ostream& operator<<(std::ostream& out, Destination obj)
{
	return out;
}
