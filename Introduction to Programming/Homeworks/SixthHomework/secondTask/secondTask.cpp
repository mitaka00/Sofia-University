#include <iostream>
#include <stdlib.h> 
#include <time.h>

using namespace std;

const int MAX_LENGTH = 100;

void fillArr(char arr[][MAX_LENGTH], const int length) {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			arr[i][j] = ' ';
		}
	}
}

void printArr(char arr[][MAX_LENGTH], const int length) {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			cout << "[ " << arr[i][j] << " ] ";
		}
		cout << endl;
	}
}

bool validateInput(char arr[][MAX_LENGTH], const int length, const int x, const int y) {
	if (x < 1 || y < 1 || x > length || y > length) {
		return false;
	}

	if (arr[x-1][y-1] == 'X' || arr[x-1][y-1] == 'O') {
		return false;
	}

	return true;
}

bool checkRow(char arr[][MAX_LENGTH], const int length) {
	bool endGame = true;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			if (arr[i][j] != arr[i][j + 1] || (arr[i][j] != 'X' && arr[i][j] != 'O')) {
				endGame = false;
				break;
			}
		}

		if (endGame) {
			return true;
		}

		endGame = true;
	}

	return false;
}

bool checkCol(char arr[][MAX_LENGTH], const int length) {
	bool endGame = true;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			if (arr[j][i] != arr[j + 1][i] || (arr[j + 1][i] != 'X' && arr[j + 1][i] != 'O')) {
				endGame = false;
				break;
			}
		}

		if (endGame) {
			return true;
		}

		endGame = true;
	}

	return false;
}

bool checkDiagonals(char arr[][MAX_LENGTH], const int length) {
	bool endGame = true;

	//Проверка за главен диагонал
	for (int i = 0; i < length - 1; i++)
	{
		if (arr[i][i] != arr[i + 1][i + 1] || (arr[i][i] != 'X' && arr[i][i] != 'O')) {
			endGame = false;
			break;
		}
	}

	if (endGame) {
		return true;
	}

	endGame = true;
	//Проверка за втори диагонал
	for (int i = 0; i < length - 1; i++)
	{
		if (arr[(length - 1) - i][i] != arr[(length - 2) - i][i + 1] || (arr[(length - 1) - i][i] != 'X' && arr[(length - 1) - i][i] != 'O')) {
			endGame = false;
			break;
		}
	}

	if (endGame) {
		return true;
	}

	return false;
}

bool checkForEnd(char arr[][MAX_LENGTH], const int length) {
	bool endGame;

	//Проверка дали има нареден ред
	endGame = checkRow(arr, length);
	if (endGame) {
		return true;
	}

	//Проверка за наредена колона
	endGame = checkCol(arr, length);
	if (endGame) {
		return true;
	}

	//Проверка за диагонали
	endGame = checkDiagonals(arr, length);
	if (endGame) {
		return true;
	}
	
	return false;
}

void findRandomPlace(char arr[][MAX_LENGTH], const int length, int& x, int& y) {
	srand(time(NULL));

	bool isReady = false;
	while (!isReady) {
		x = 1 + rand() % length;
		y = 1 + rand() % length;

		isReady = validateInput(arr, length, x, y);
	}
}

void printResult(int counter, int input) {
	if (counter % 2 == 0) {
		cout << "Player 1 won!" << endl;
	}
	else {
		if (input == 2) {
			cout << "Computer won!" << endl;
		}
		else {
			cout << "Player 2 won!" << endl;
		}
	}
}

void playGame(char arr[][MAX_LENGTH], const int length,const int input) {
	bool endGame = false;

	int counter = 0;
	int x, y;

	while (!endGame && counter < length * length) {
		if (counter % 2 == 0 || input==1) {
			cin >> x >> y;

			bool isValidInput = validateInput(arr, length, x, y);
			if (!isValidInput) {
				cout << "Invalid input. Please try again." << endl;
				continue;
			}
		}
		else if (input == 2) {
			findRandomPlace(arr, length, x, y);
		}
				
		if (counter % 2 == 0) {
			arr[x - 1][y - 1] = 'X';
		}
		else {
			arr[x - 1][y - 1] = 'O';
		}
	
		endGame = checkForEnd(arr, length);

		if (input == 1 || counter % 2 == 1 || endGame) {
			printArr(arr, length);
		}
	
		if (endGame) {
			printResult(counter, input);
		}

		counter++;
	}

	if (!endGame) {
		cout << "No winner";
	}
}

int main() {
	int input,length;

	cout << "Choose game mode (1 - PvP, 2 - PvC):";
	cin >> input;

	cout << "Enter grid size: ";
	cin >> length;

	if (!cin || (input != 1 && input != 2) || length < 0 || length > MAX_LENGTH) {
		cout << "Invalid input";
		return 0;
	}

	char arr[MAX_LENGTH][MAX_LENGTH];
	bool endGame = false;

	fillArr(arr, length);

	printArr(arr, length);
	cout << "Please enter x and y: ";

	playGame(arr, length, input);

	return 0;
}