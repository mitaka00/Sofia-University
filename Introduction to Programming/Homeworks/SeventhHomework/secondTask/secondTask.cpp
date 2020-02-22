#include <iostream>
#include <stdlib.h> 
#include <time.h>
using namespace std;

int const MAX_LENGTH = 52;

void fillDeck(int deck[]) {
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		cin >> deck[i];
	}
	cout << endl;
}

void showDeck(int deck[]) {
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		cout << deck[i] << " ";
	}
	cout << endl;
}

//���������� ����� ����� ������� �����
bool isForChanging(int deck[], int firstIndex, int secondIndex) {
	int firstCard = deck[firstIndex];
	int secondCard = deck[secondIndex];

	int firstCardType = firstCard / 100;
	int firstCardValue = firstCard % 100;
	int secondCardType = secondCard / 100;
	int secondCardValue = secondCard % 100;

	//�������� ������ ���
	if (firstCardValue == 1 && secondCardValue != 1) {
		return false;
	}
	else if (firstCardValue != 1 && secondCardValue == 1) {
		return true;
	}
	else if (firstCardValue == 1 && secondCardValue == 1) {
		if (firstCardType > secondCardType) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		//�������� ������ ���������� �����
		if (firstCardValue < secondCardValue) {
			return true;
		}
		else if (firstCardValue > secondCardValue) {
			return false;
		}
		else {
			if (firstCardType > secondCardType) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	
}

void swap(int deck[],int firstIndex,int secondIndex) {
	int x = deck[firstIndex];
	deck[firstIndex] = deck[secondIndex];
	deck[secondIndex] = x;
}

void sortDeck(int deck[]) {
	bool changed = false;
	unsigned sorted = 0;
	do {
		changed = false;

		for (int i = MAX_LENGTH - 1; i > sorted; i--) {
			if (isForChanging(deck,i,i-1)) 
			{ 
				swap(deck, i, i - 1);
				changed = true;
			}
		}
		sorted++;
	} while (changed);
}

//����������� �� �������
void randomShuffle(int buffer[], int deck[]) {
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		int card = deck[i];
		bool isSearching = true;
		while (isSearching) {
			int index = rand() % 52;
			if (buffer[index] == 0) {
				buffer[index] = deck[i];
				isSearching = false;
			}
		}
	}
}

void shuffleDeck(int deck[]) {
	int buffer[MAX_LENGTH];

	//fill deck with 0
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		buffer[i] = 0;
	}

	//������ ������ �� ����������� �� �������
	randomShuffle(buffer,deck);

	//������������ �� ������� ��� �����������
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		deck[i] = buffer[i];
	}
}

//������ �����, �� ��������� ������ �� ��������� �� ���������, �� ��������� ����� ���� ������ �� ����������� �� �����
//��� ����� ������ � ��������, �� ����������� �� ��� ������� �� ������ � ������ �� ����, �� ���� �� �� �������� ���� �������� �� ������ ����� �����, �� ������ �� �.
int main() {
	srand(time(NULL));
	int deck[MAX_LENGTH];

	fillDeck(deck);

	cout << "Sorted:" << endl;
	sortDeck(deck);
	showDeck(deck);

	cout << "Shuffled: " << endl;
	shuffleDeck(deck);
	showDeck(deck);

	cout << "Sorted again: " << endl;
	sortDeck(deck);
	showDeck(deck);

	return 0;
}