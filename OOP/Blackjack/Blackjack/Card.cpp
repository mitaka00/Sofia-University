#include "Card.h"
#include <iostream>
#include <cstring>
#include <stdlib.h> 
#include <time.h>  

const int MAX_CARD_SIZE = 5;
const int VALUES_LENGTH = 13;
const int VALUE_NAME_LENGTH = 3;
const int SUITS_LENGTH = 4;
const int SUITS_NAME_LENGTH = 8;

char values[VALUES_LENGTH][VALUE_NAME_LENGTH] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
char suits[SUITS_LENGTH][SUITS_NAME_LENGTH] = { "club","diamond","heart","spade" };

unsigned Card::currID = 0;

unsigned Card::getID()
{
	return currID++;
}

Card::Card(const char* id,int value,int suit)
{
	getID();
	char token[MAX_CARD_SIZE];
	itoa(currID, token, 10);
	this->id = new char[strlen(id) + strlen(token) + 1];
	strcpy(this->id, id);
	strcat(this->id, token);

	if (strcmp(id, "Default") == 0) {
		generateDefaultCard(value, suit);
	}
	else {
		generateRandomCard();
	}
}

Card::Card(const Card& other)
{
	copy(other);
}

Card& Card::operator=(const Card& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}

	return *this;
}

Card::~Card()
{
	clear();
}

bool Card::operator==(const Card& other) const
{
	if (strcmp(other.suit, suit) == 0 && strcmp(other.value, value) == 0) {
		return true;
	}

	return false;
}

void Card::generateRandomCard()
{
	int randomSuitIndex = rand() % SUITS_LENGTH;
	suit = new char [strlen(suits[randomSuitIndex]) + 1];
	strcpy(suit, suits[randomSuitIndex]);

	int randomValueIndex = rand() % VALUES_LENGTH;
	value = new char[strlen(values[randomValueIndex]) + 1];
	strcpy(value, values[randomValueIndex]);
}

void Card::generateDefaultCard(int value, int suit)
{
	this->suit = new char[strlen(suits[suit]) + 1];
	strcpy(this->suit, suits[suit]);
	this->value = new char[strlen(values[value]) + 1];
	strcpy(this->value, values[value]);
	
}

void Card::copy(const Card& other)
{
	id = new char[strlen(other.id) + 1];
	strcpy(id, other.id);

	suit = new char[strlen(other.suit) + 1];
	strcpy(suit, other.suit);

	value = new char[strlen(other.value) + 1];
	strcpy(value, other.value);
}

void Card::clear()
{
	delete[] id;
	delete[] suit;
	delete[] value;
	suit = nullptr;
	id = nullptr;
	value = nullptr;
}

std::ostream& operator<<(std::ostream& out, const Card& obj)
{
	out << obj.getValue() << "(" << obj.getSuit() << ")";
	return out;
}
