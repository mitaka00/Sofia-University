#include "Date.h"
#include <cstdlib>
const int MAXN_LENGTH = 32;

Date::Date(int year, int month, int day) :
	year(year),
	month(month),
	day(day)
{}

Date& Date::operator=(Date & other)
{
	year = other.year;
	month = other.month;
	day = other.day;

	return *this;
}

std::ostream& operator<<(std::ostream& out, Date& obj)
{
	out << obj.getYear() << "-" << obj.getMonth() << "-" << obj.getDay();
	return out;
}

std::istream& operator>>(std::istream& in, Date& obj)
{
	char input[MAXN_LENGTH];
	in.getline(input, MAXN_LENGTH);

	char* tokens;
	tokens = strtok(input, "-");
	obj.setYear(atoi(tokens));
	
	tokens = strtok(nullptr, "-");
	obj.setMonth(atoi(tokens));
	
	tokens = strtok(nullptr, "-");
	obj.setDay(atoi(tokens));

	return in;
}
