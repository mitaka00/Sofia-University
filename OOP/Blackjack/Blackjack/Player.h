#pragma once
#include <fstream>
class Player
{
public:
	Player(const char* name="",int age=0);
	Player(const Player& other);
	Player& operator=(const Player& other);
	~Player();

	void deserialize(std::ifstream& in);
	void serialize(std::ofstream& out)const;

	void addCurrentPoints(const int points);
	void getWin();
	void getLoose();

	const char* getName() const { return name; };
	const int getCurrentPoints()const { return currentPoints; };

	friend std::ostream& operator<<(std::ostream& out, const Player& obj);

private:
	char* name;
	int age;
	unsigned int games;
	unsigned int wins;
	double coefficientWins;
	unsigned int currentPoints;

	void copy(const Player& other);
	void clear();
};

