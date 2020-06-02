#pragma once
#include <iostream>
#include <fstream>
class Date
{
public:
	Date(int year=0,int month=0,int day=0);
	Date& operator=(const Date& other);

	bool operator<=(const Date& other)const;
	void serialize(std::ofstream& out) const;
	void deserialize(std::ifstream& in);
	bool isTrueDate()const;

	void setYear(int year) { this->year = year; };
	void setMonth(int month) { this->month = month; };
	void setDay(int day) { this->day = day; };

	int getYear() const { return year; };
	int getMonth() const { return month; };
	int getDay() const { return day; };
private:
	int year;
	int month;
	int day;
};

std::ostream& operator<<(std::ostream& out,const Date& obj);
std::istream& operator>>(std::istream& in,Date& obj);

