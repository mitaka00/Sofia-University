#pragma once
#include "Deck.h"
#include "Player.h"
#include "Card.h"
#include <fstream>
class System {

public:
	static System& i();

	System(const System&) = delete;
	void operator=(const System&) = delete;
	~System();

	void run();
	void showPlayers() const;
	double calcProbability() const ;

	bool readPlayers();
	void writePlayers();
	bool checkName(char* name);

private:
	System();

	Player* players;
	int playersCount;

	Deck deck;
	Player currentPlayer;
	int dealerPoints;
	bool isPlayerfinished;

	int includePlayer(const char* name);
	void setPlayer(const char* name);
	void savePlayers();
	void setDeck(char* token);
	const int convertPoints(const char* points) const;
	bool firstPlayerGame();
	void dealerGame();
	bool isTrueName(const char* name);
};

