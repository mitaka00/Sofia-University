#pragma once
#include<iostream>
const int MAX_LENGTH = 127;
class Beer
{
public:
	Beer();
	Beer(const char* brand, double volume);

	double getVolume();
	void setVolume(double volume);
	const char* getBrand();
	void setBrand(const char* brand);

	void addBeer(Beer beer);

	bool check(char* brand);

private:
	char brand[MAX_LENGTH];
	double volume;
};

