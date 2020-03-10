#include "Beer.h";
#include <iostream>
using namespace std;

int main() {
	Beer firstBeer("Stella Artois", 500);
	Beer secondBeer("Heinken", 250);
	firstBeer.addBeer(secondBeer);
	cout << firstBeer.getBrand() << firstBeer.getVolume();

	return 0;
}