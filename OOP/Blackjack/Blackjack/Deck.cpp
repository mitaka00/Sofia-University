#include "Deck.h"
#include <cstring>
#include <iostream>
const int DEFAULT_SIZE = 8;
const int CUSTOM_SIZE = 7;

Deck::Deck(int capacity, const char* id):
	capacity(capacity),
	drawedCards(0),
	cards(new Card[capacity])
{
	if (capacity == 52) {
		this->id = new char[DEFAULT_SIZE];
		strcpy(this->id, "Default");
	}
	else if (strcmp(id,"")==0) {
		this->id = new char[CUSTOM_SIZE];
		strcpy(this->id, "Custom");
	}
	else {
		this->id = new char[strlen(id)+1];
		strcpy(this->id, id);
	}

	if (capacity == 52) {
		generateDefaultDeck();
	}
	else {
		generateRandomDeck();
	}
}

Deck::Deck(const Deck& other)
{
	copy(other);
}

Deck& Deck::operator=(const Deck& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}

	return *this;
}

Deck::~Deck()
{
	clear();
}

Card& Deck::operator[](int index)
{
	return cards[index];
}

const Card& Deck::operator[](int index) const
{
	return cards[index];
}

void Deck::push(const Card& card)
{
	cards[drawedCards] = card;
	drawedCards++;
}

void Deck::shuffle()
{
	for (int i = 0; i < 200; i++)
	{
		int firstIndex = rand() % capacity;
		int secondIndex = rand() % capacity;
		this->swap(firstIndex, secondIndex);
	}
}

Card& Deck::draw()
{
	if (drawedCards == capacity - 1) {
		drawedCards = 0;
	}
	swap(drawedCards, capacity-drawedCards - 1);
	drawedCards++;
	return cards[capacity-drawedCards-1];
}

void Deck::swap(int firstIndex, int secondIndex)
{
	if (firstIndex < 0 || secondIndex < 0 || firstIndex >= capacity || secondIndex >= capacity) {
		std::cout << "Invalid index of cards" << std::endl;
	}
	else {
		std::swap(cards[firstIndex], cards[secondIndex]);
	}
}

int Deck::suit_count(const char* suit) const
{
	int counter = 0;
	for (int i = 0; i < capacity; i++)
	{
		if (strcmp(cards[i].getSuit(), suit) == 0) {
			counter++;
		}
	}

	return counter;
}

int Deck::rank_count(const char* value) const
{
	int counter = 0;
	for (int i = 0; i < capacity - drawedCards; i++)
	{
		if (strcmp(cards[i].getValue(),value)==0) {
			counter++;
		}
	}

	return counter;
}

bool Deck::include(const Card& card) const
{
	int counter = 1;
	for (int i = 0; i < capacity; i++)
	{
		if (cards[i] == card) {
			if (capacity <= 52) {
				return true;
			}
			else if (counter == capacity / 52 + 1) {
				return true;
			}
			counter++;
		}
	}
	return false;
}

void Deck::generateRandomDeck()
{
	int counter = 0;
	while (counter != capacity) {
		Card card(id);
		if (!include(card)) {
			counter++;
			push(card);
		}
	}

	drawedCards = 0;
}

void Deck::generateDefaultDeck()
{
	for (int value = 0; value < 13; value++)
	{
		for (int suit = 0; suit < 4; suit++)
		{
			Card card(id, value, suit);
			push(card);
		}
	}
	shuffle();
}

void Deck::copy(const Deck& other)
{
	drawedCards = 0;
	capacity = other.capacity;
	cards = new Card[capacity];
	for (int i = 0; i < capacity; i++)
	{
		cards[i] = other.cards[i];
	}

	id = new char[strlen(other.id) + 1];
	strcpy(id, other.id);
}

void Deck::clear()
{
	delete[] id;
	id = nullptr;
	delete[] cards;
	cards = nullptr;
}

std::ostream& operator<<(std::ostream& out, const Deck& obj)
{
	for (int i = 0; i < obj.getCapacity(); i++)
	{
		out << obj.cards[i];
	}

	return out;
}
