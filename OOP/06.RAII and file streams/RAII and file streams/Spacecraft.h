#pragma once
#include <fstream>
class Spacecraft
{
public:
	Spacecraft(int year = 0, const char* name = "");
	Spacecraft(const Spacecraft& other);
	Spacecraft(std::ifstream& in);
	Spacecraft& operator=(const Spacecraft& other);
	~Spacecraft();

	void serialize(std::ofstream& out) const;

	inline int getYear()const;
	inline const char* getName()const;
	
private:
	int year;
	char* name;
	void copy(const Spacecraft& other);
	void clear();
};

std::ostream& operator<<(std::ostream& out,const Spacecraft& obj);

