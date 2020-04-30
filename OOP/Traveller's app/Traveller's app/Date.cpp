#include "Date.h"
#include <cstdlib>
const int MAXN_LENGTH = 32;
const int CURRENT_YEAR = 2020;

Date::Date(int year, int month, int day) :
	year(year),
	month(month),
	day(day)
{}

Date& Date::operator=(const Date & other)
{
	year = other.year;
	month = other.month;
	day = other.day;

	return *this;
}

bool Date::operator<=(const Date& other) const
{
	if (year < other.year) {
		return true;
	}
	else if (year > other.year) {
		return false;
	}
	else {
		if (month < other.month) {
			return true;
		}
		else if (month > other.month) {
			return false;
		}
		else {
			if (day <= other.day) {
				return true;
			}
			else if (day > other.day) {
				return false;
			}
		}
	}
}

void Date::serialize(std::ofstream& out) const
{
	out.write((const char*)&year, sizeof(year));
	out.write((const char*)&month, sizeof(month));
	out.write((const char*)&day, sizeof(day));
}

void Date::deserialize(std::ifstream& in)
{
	in.read((char*)&year, sizeof(year));
	in.read((char*)&month, sizeof(month));
	in.read((char*)&day, sizeof(day));
}

std::ostream& operator<<(std::ostream& out, Date& obj)
{
	out << obj.getYear() << "-" << obj.getMonth() << "-" << obj.getDay();
	return out;
}

std::istream& operator>>(std::istream& in, Date& obj)
{
	char input[MAXN_LENGTH];
	in >> input;

	char* tokens;
	tokens = strtok(input, "-");
	if (tokens == nullptr) {
		obj.setYear(0);
	}
	else {
		obj.setYear(atoi(tokens));
	}
	
	tokens = strtok(nullptr, "-");
	if (tokens == nullptr) {
		obj.setMonth(0);
	}
	else {
		obj.setMonth(atoi(tokens));
	}
	
	tokens = strtok(nullptr, "-");
	if (tokens == nullptr) {
		obj.setDay(0);
	}
	else {
		obj.setDay(atoi(tokens));
	}
	return in;
}

bool Date::isTrueDate() const
{
	if (day <= 0 || day>31 || year <= 0 || year>CURRENT_YEAR || month <= 0 || month>12) {
		return false;
	}
	return true;
}
