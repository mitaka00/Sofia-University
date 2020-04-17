#include "Player.h"
#include <cstring>

Player::Player(const char* name, int age):
	name(new char[strlen(name)+1]),
	age(age),
	wins(0),
	coefficientWins(0),
	currentPoints(0),
	games(0)
{
	strcpy(this->name, name);
}

Player::Player(const Player& other)
{
	copy(other);
}

Player& Player::operator=(const Player& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}

	return *this;
}

Player::~Player()
{
	clear();
}

void Player::deserialize(std::ifstream& in)
{
	clear();
	int len;
	in.read((char*)&len, sizeof(len));
	name = new char[len];
	in.read((char*)name, len);
	in.read((char*)&age, sizeof(age));
	in.read((char*)&games, sizeof(games));
	in.read((char*)&wins, sizeof(wins));
	in.read((char*)&coefficientWins, sizeof(coefficientWins));
	currentPoints = 0;
}

void Player::serialize(std::ofstream& out) const
{
	int len = strlen(name) + 1;
	out.write((char*)&len, sizeof(len));
	out.write((char*)name, len);
	out.write((char*)&age, sizeof(age));
	out.write((char*)&games, sizeof(games));
	out.write((char*)&wins, sizeof(wins));
	out.write((char*)&coefficientWins, sizeof(coefficientWins));
	
}

void Player::addCurrentPoints(const int points)
{
	currentPoints += points;
}

void Player::getWin()
{
	games += 1;
	wins += 1;
	coefficientWins = wins / (double)games;
}

void Player::getLoose()
{
	games += 1;
	coefficientWins = wins / (double)games;
}

void Player::copy(const Player& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	age = other.age;
	wins = other.wins;
	games = other.games;
	coefficientWins = other.coefficientWins;
	currentPoints = other.currentPoints;
}

void Player::clear()
{
	delete[] name;
	name = nullptr;
}

std::ostream& operator<<(std::ostream& out, const Player& obj)
{
	out << obj.name << " " << obj.wins << " " << obj.coefficientWins << std::endl;
	return out;
}
