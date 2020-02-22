#include <iostream>
#include <stdlib.h> 
#include <time.h>

using namespace std;
unsigned long const MAX_VALUE = 9'223'372'036'854'775'807;

unsigned long randomKey() {
	return rand()*rand();
}

void search(unsigned long key,int& count,int random) {
	long searchNum = randomKey();
	long minValue = 0;
	long maxValue = MAX_VALUE;

	bool isSearching = true;

	if (random) {
		cout << "Random searching start:" << endl;
	}
	else {
		cout << "Default searching start:" << endl;
	}

	while (isSearching)
	{
		cout << searchNum << endl;
		if (searchNum == key) {
			cout << "Key is " << searchNum << endl;
			isSearching = false;
		}
		else {
			if (key < searchNum) {
				maxValue = searchNum;
			}
			else {
				minValue = searchNum;
			}

			if (random) {
				long differenceBetweenMaxAndMin = maxValue - minValue;
				searchNum = minValue + randomKey() % differenceBetweenMaxAndMin+1;
			}
			else {
				searchNum = (maxValue + minValue) / 2;
			}
			
			count++;
		}
	}
}

int main() {
	srand(time(NULL));
	unsigned long key = randomKey();
	cout << "Key= " << key << endl;

	int firstCounter = 1, secondCounter = 1;
	int random = true;

	search(key, firstCounter, !random);
	search(key, secondCounter, random);

	cout << endl;
	cout << "Default binary searching: " << firstCounter << " tries" << endl;
	cout << "Random binary searching: " << secondCounter << " tries" << endl;

	return 0;
}