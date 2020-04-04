#include "Beer.h"
#include <iostream>

Beer::Beer()
{
	strcpy(brand, "");
	volume = 0.0;
}

Beer::Beer(const char* brand, double volume) :Beer()
{
	setBrand(brand);
	setVolume(volume);
}

double Beer::getVolume()
{
	return volume;
}

void Beer::setVolume(double volume)
{
	if (volume >= 0) {
		this->volume = volume;
	}
}

const char* Beer::getBrand()
{
	return brand;
}

void Beer::setBrand(const char* brand)
{
	strcpy(this->brand, brand);
}

void Beer::addBeer(Beer beer)
{
	strcat(strcat(this->brand, "&"), beer.brand);
	this->volume += beer.volume;
}

bool Beer::check(char* brand)
{
	return true;
}
