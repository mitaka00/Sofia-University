#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "System.h"
#include <stdlib.h> 
#include <time.h> 

int main() {
	srand(time(NULL));

	System::i().run();

	return 0;
}