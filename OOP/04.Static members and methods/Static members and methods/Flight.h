#pragma once
class Flight
{
public:
	Flight(const char* departure = "", const char* locations = "", double price = 0);
	Flight(const Flight& other);
	Flight& operator=(const Flight& other);
	~Flight();

private:
	int id;
	char* departure;
	char* locations;
	double price;

	static int getId();
	static int currentId;

	void copy(const Flight& other);
	void clear()
};

