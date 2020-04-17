#pragma once
#include <iostream>
class Card
{
public:
	Card(const char* id = "",int value=0,int suit=0);
	Card(const Card& other);
	Card& operator=(const Card& other);
	~Card();

	const char* getSuit()const { return suit; };
	const char*  getValue()const { return value; };

	bool operator==(const Card& other)const;

private:
	char* suit;
	char* value;
	char* id;

	static unsigned getID();
	static unsigned currID;

	void generateRandomCard();
	void generateDefaultCard(int value,int suit);

	void copy(const Card& other);
	void clear();
};

std::ostream& operator<<(std::ostream& out, const Card& obj);

