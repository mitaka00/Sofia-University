#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h> 
#include <time.h> 
#include "System.h"

const int TOKENS_LENGTH = 30;

const char* fileName = "players.db";

System::System()
{
	char input[TOKENS_LENGTH];
	if (readPlayers()) {
		showPlayers();
		std::cout << "Choose a player or enter a new player"<<std::endl;
	}
	else {
		playersCount = 0;
		std::cout << "No player in database. Please enter a new Player:"<<std::endl;
	}
	
	bool isGoodName = true;
	do {
		if (!isGoodName) {
			std::cout << "Invalid name. Please try again: ";
		}
		std::cin.getline(input, TOKENS_LENGTH);
		isGoodName = false;
	} while (!checkName(input));
	setPlayer(input);

	std::cout << "You will play as " << input << ". Choose the size of deck:";
	std::cin.ignore();
	std::cin.getline(input, TOKENS_LENGTH);
	setDeck(input);
}

bool System::readPlayers()
{
	std::ifstream in(fileName, std::ios::binary);
	if (!in) {
		return false;
	}
	
	in.read((char*)&playersCount, sizeof(playersCount));
	players = new Player[playersCount];
	for (int i = 0; i < playersCount; i++)
	{
		players[i].deserialize(in);
	}
	return true;
}

void System::writePlayers()
{
	std::ofstream out(fileName, std::ios::binary);
	if (!out) {
		std::cout << "Error";
	}

	out.write((char*)&playersCount, sizeof(playersCount));
	for (int i = 0; i < playersCount; i++)
	{
		players[i].serialize(out);
	}
}

void System::setPlayer(const char* name)
{
	int index = includePlayer(name);
	if (index!=-1) {
		currentPlayer = players[index];
	}
	else {
		int age;
		do {
			std::cout << "Please enter your age: ";
			std::cin >> age;
			if (age < 18 || age > 90) {
				std::cout << "You have to be between 18 and 90 years." << std::endl;
			}
		} while (age < 18 || age>90);

		currentPlayer = Player(name, age);
	}
}

void System::setDeck(char* token)
{
	char* series = strtok(token, " ");
	int deckCapacity = atoi(series);
	series = strtok(nullptr, " ");
	if (series) {
		deck = Deck(deckCapacity, series);
	}
	else {
		deck = Deck(deckCapacity);
	}
}

void System::run()
{
	std::cout << "Start!" << std::endl;

	if (!firstPlayerGame()) {
		std::cout << "You loose!" << std::endl;
		currentPlayer.getLoose();
	}
	else {
		dealerPoints = 0;
		dealerGame();
		if (dealerPoints > 21 || dealerPoints <= currentPlayer.getCurrentPoints()) {
			std::cout << "You win!" << std::endl;
			currentPlayer.getWin();
		}
		else {
			std::cout << "You loose!" << std::endl;
			currentPlayer.getLoose();
		}
	}

	savePlayers();
}

void System::savePlayers()
{
	int index = includePlayer(currentPlayer.getName());
	if (index != -1) {
		players[index] = currentPlayer;
	}
	else {
		playersCount += 1;
		Player* newPlayers = new Player[playersCount];
		for (int i = 0; i < playersCount-1; i++)
		{
			newPlayers[i] = players[i];
		}
		newPlayers[playersCount-1] = currentPlayer;
		delete[] players;
		players = newPlayers;
	}

	writePlayers();
}

System& System::i()
{
	static System instance;
	return instance;
}

System::~System()
{
	delete[] players;
	std::cout << "Have a nice day!" << std::endl;
}

void System::showPlayers() const
{
	for (int i = 0; i < playersCount; i++)
	{
		std::cout << players[i];
	}
}

double System::calcProbability() const
{
	double count = deck.getCapacity() - deck.getDrawedCards();
	int neededPoints = 21 - currentPlayer.getCurrentPoints();
	if (neededPoints > 11) {
		return 0;
	}
	double goodCards = 0;
	for (int i = 0; i < count; i++)
	{
		if (convertPoints(deck[i].getValue()) == neededPoints) {
			goodCards++;
		}
	}

	if (count == 0) {
		return 0;
	}
	return goodCards / count;
}

const int System::convertPoints(const char* points) const
{
	if (strcmp(points, "J") == 0 || strcmp(points, "K") == 0 || strcmp(points, "Q") == 0) {
		return 10;
	}
	else if (strcmp(points, "A") == 0) {
		if (!isPlayerfinished) //The points which 'A' gives to  the player
		{
			if (currentPlayer.getCurrentPoints() <= 10) {
				return 11;
			}
			else {
				return 1;
			}
		} //The points which 'A' gives to the dealer
		else {
			if (dealerPoints + 11 > 21) {
				return 11;
			}
			return 1;
		}
		
	}
	else {
		return atoi(points);
	}
}

bool System::firstPlayerGame()
{
	isPlayerfinished = false;
	Card currentCard = deck.draw();
	currentPlayer.addCurrentPoints(convertPoints(currentCard.getValue()));
	std::cout << currentCard << "	(Points: " << currentPlayer.getCurrentPoints() << ")" << std::endl;

	char input[TOKENS_LENGTH];
	for (;;) {
		if (currentPlayer.getCurrentPoints() > 21) {
			return false;
		}
		std::cout << "hit/stand/probability" << std::endl;
		std::cin >> input;

		if (strcmp(input, "hit") == 0) {
			currentCard = deck.draw();
			currentPlayer.addCurrentPoints(convertPoints(currentCard.getValue()));
			std::cout << currentCard << "	(Points: " << currentPlayer.getCurrentPoints() << ")" << std::endl;
		}
		else if (strcmp(input, "stand") == 0) {
			break;
		}
		else if (strcmp(input, "probability") == 0) {
			std::cout << calcProbability() << std::endl;
		}
		else {
			std::cout << "Unknown command! Please try again." << std::endl;
		}
	}

	return true;
}

void System::dealerGame()
{
	isPlayerfinished = true;
	std::cout << "The dealer's draw: ";
	do {
		Card currentCard = deck.draw();
		std::cout << currentCard << " ";
		dealerPoints +=convertPoints(currentCard.getValue());

	} while (dealerPoints <= 17);

	std::cout << "	(Points: " << dealerPoints << ")" << std::endl;
}

bool System::isTrueName(const char* name)
{
	int length = strlen(name);
	if (name[0] < 'A' || name[0]>'Z') {
		return false;
	}
	for (int i = 1; i < length; i++)
	{
		if (name[i] < 'a' || name[i]>'z') {
			return false;
		}
	}

	return true;
}

bool System::checkName(char* name)
{
	char* token = strtok(name, " ");
	char firstName[TOKENS_LENGTH];
	strcpy(firstName, token);
	if (!isTrueName(firstName)) {
		return false;
	}

	token = strtok(nullptr, " ");
	if (!token) {
		return false;
	}
	char secondName[TOKENS_LENGTH];
	strcpy(secondName, token);
	if (!isTrueName(secondName)) {
		return false;
	}

	strcpy(name, firstName);
	strcat(name, " ");
	strcat(name, secondName);
	return true;
}

int System::includePlayer(const char* name)
{
	for (int i = 0; i < playersCount; i++)
	{
		if (strcmp(players[i].getName(), name) == 0) {
			return i;
		}
	}
	return -1;
}
