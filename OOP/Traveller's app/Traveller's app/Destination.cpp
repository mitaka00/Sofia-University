#include "Destination.h"
#include <iostream>
#include <fstream>

using std::string;
Destination::Destination(const string& name, int grade, const string& comment, Date start, Date end) :
	name(name),
	grade(grade),
	comment(comment),
	start(start),
	end(end)
{}

//Write destination in file
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

//Read destination from file
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

//Add image
void Destination::addImage(const string& imageName)
{
	images.push_back(imageName);
}

//Print destination on console
std::ostream& operator<<(std::ostream& out,const Destination& obj)
{
	std::cout << "Name:" << obj.name << std::endl;;
	std::cout << "Grade:" << obj.grade << std::endl;
	std::cout << "Starting date: " << obj.start << std::endl;
	std::cout << "Ending date: " << obj.end << std::endl;
	std::cout << "Comment:" << obj.comment << std::endl;

	std::cout << "Images: " << std::endl;
	int len = obj.images.size();
	if (len == 0) {
		std::cout << "No images";
	}
	else {
		for (int i = 0; i < len; i++)
		{
			std::cout << obj.images[i] << std::endl;
		}
	}
	return out;
}
