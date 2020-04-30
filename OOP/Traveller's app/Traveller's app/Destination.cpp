#include "Destination.h"
#include <iostream>
#include <fstream>

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
	int len = name.length();
	out.write((const char*)&len, sizeof(len));
	out.write((const char*)&name[0], len);

	out.write((const char*)&grade, sizeof(grade));

	len = comment.length();
	out.write((const char*)&len, sizeof(len));
	out.write((const char*)&comment[0], len);

	start.serialize(out);
	end.serialize(out);

	len = images.size();
	out.write((const char*)&len, sizeof(len));
	for (int i = 0; i < len; i++)
	{
		int currentLen = images[i].length();
		out.write((const char*)&currentLen, sizeof(currentLen));
		out.write((const char*)&images[i][0], currentLen);
	}
}

void Destination::deserialize(std::ifstream& in)
{
	int len;
	in.read((char*)&len, sizeof(len));
	name.resize(len);
	in.read((char*)&name[0], len);

	in.read((char*)&grade, sizeof(grade));

	in.read((char*)&len, sizeof(len));
	comment.resize(len);
	in.read((char*)&comment[0], len);

	start.deserialize(in);
	end.deserialize(in);

	in.read((char*)&len, sizeof(len));
	images.resize(len);
	for (int i = 0; i < len; i++)
	{
		int currentLen;
		in.read((char*)&currentLen, sizeof(currentLen));
		images[i].resize(currentLen);
		in.read((char*)&images[i][0], currentLen);
	}
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
	std::cout << "Name:" << obj.name << std::endl;;
	std::cout << "Grade:" << obj.grade << std::endl;
	std::cout << "Starting date: " << obj.start << std::endl;
	std::cout << "Ending date: " << obj.end << std::endl;
	std::cout << "Comment:" << obj.comment << std::endl;

	std::cout << "Images: " << std::endl;
	int len = obj.images.size();
	for (int i = 0; i < len; i++)
	{
		std::cout << obj.images[i] << std::endl;
	}

	return out;
}
