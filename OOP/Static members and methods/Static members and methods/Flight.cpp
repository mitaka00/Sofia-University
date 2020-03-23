#include "Flight.h"
#include <cstring>

int Flight::currentId = 0;

int Flight::getId()
{
	return currentId++;
}

Flight::Flight(const char* departure, const char* locations, double price)
	: departure(new char[strlen(departure) + 1]),
	locations(new char[strlen(locations) + 1]),
	price(price),
	id(getId())
{
	strcpy(this->departure, departure);
	strcpy(this->locations, locations);
}

Flight::Flight(const Flight& other)
{
	copy(other);
}

Flight& Flight::operator=(const Flight& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

Flight::~Flight()
{
	clear();
}

void Flight::copy(const Flight& other)
{
	price = other.price;
	id = other.id;
	departure = new char[strlen(other.departure) + 1];
	locations = new char[strlen(other.locations) + 1];
	strcpy(departure, other.departure);
	strcpy(locations, other.locations);
}

void Flight::clear()
{
	delete[] departure;
	delete[] locations;
	departure = nullptr;
	locations = nullptr;
}
