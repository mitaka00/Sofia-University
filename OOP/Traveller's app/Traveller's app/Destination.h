#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "Date.h"

using string = std::string;
class Destination
{
public:
	Destination(const string name = "", int grade = 1, const string comment = "", Date start = Date(), Date end = Date());

	void serialize(std::ofstream& out)const;
	void deserialize(std::ifstream& in);
	void addImage(const string imageName);

	inline string getName() const  { return name; };
	inline string getComment() const { return comment; };
	const inline int getGrade() const { return grade; };

	friend std::ostream& operator<<(std::ostream& out, Destination obj);
private:
	string name;
	int grade;
	string comment;
	Date start;
	Date end;

	std::vector<string>images;
};



