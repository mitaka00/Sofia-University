#include "Destination.h"
#include <iostream>

Destination::Destination(const char* name, int grade, const char* comment, Date start, Date end) :
	name(new char[strlen(name) + 1]),
	grade(grade),
	comment(new char[strlen(comment) + 1]),
	start(start),
	end(end)
{
	strcpy(this->name, name);
	strcpy(this->comment, comment);
}

Destination::Destination(Destination& other)
{
	copy(other);
}

Destination& Destination::operator=(Destination& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

Destination::~Destination()
{
	clear();
}

/*void Destination::addImage(const char* imageName)
{
	images[imagesCount] = new char[strlen(imageName) + 1];
	strcpy(images[imagesCount], imageName);
	imagesCount++;
}*/

void Destination::clear()
{
	delete[] name;
	delete[] comment;
	/*for (int i = 0; i < imagesCount; i++)
	{
		delete[] images[i];
	}
	delete[] images;*/

	name = nullptr;
	comment = nullptr;
}

void Destination::copy(Destination& other)
{
	name = new char[strlen(other.name)];
	strcpy(name, other.name);

	grade = other.grade;

	comment = new char[strlen(other.comment)];
	strcpy(comment, other.comment);

	start = other.start;
	end = other.end;

	Images = other.Images;
}

std::ostream& operator<<(std::ostream& out, Destination obj)
{
	return out;
}
