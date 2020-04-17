#pragma once
#include "Card.h"
class Deck
{
public:
	Deck(int capacity=0, const char* id = "");
	Deck(const Deck& other);
	Deck& operator=(const Deck& other);
	~Deck();

	Card& operator[](int index);
	const Card& operator[](int index) const;
	void shuffle();

	Card& draw();
	void swap(int firstIndex, int secondIndex);
	int suit_count(const char* suit) const; //Броя на картите с тази боя от цялото тесте
	int rank_count(const char* value) const; //Броя на картите с тази стойност от НЕИЗТЕГЛЕНИТЕ


	const int getCapacity()const { return capacity; };
	const int getDrawedCards()const { return drawedCards; };

	friend std::ostream& operator<<(std::ostream& out, const Deck& obj);

private:
	char* id;

	Card* cards;
	int drawedCards=0;
	int capacity;

	void push(const Card& card);
	bool include(const Card& card) const;
	void generateRandomDeck();
	void generateDefaultDeck();

	void copy(const Deck& other);
	void clear();
};
