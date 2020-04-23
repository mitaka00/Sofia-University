#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include "Date.h"

class Destination
{
public:
	Destination(const char* name = "", int grade = 1, const char* comment = "", Date start = Date(), Date end = Date());
	Destination(Destination& other);
	Destination& operator=(Destination& other);
	~Destination();

	void addImage(const char* imageName);

private:
	char* name;
	int grade;
	char* comment;
	Date start;
	Date end;

	std::vector<char*>Images;

	void clear();
	void copy(Destination& other);
};

std::ostream& operator<<(std::ostream& out,Destination obj);

