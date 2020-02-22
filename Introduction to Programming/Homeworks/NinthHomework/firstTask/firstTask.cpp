#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WORDS = 5;
const int COL = 5;
const int MAX_WORD_SIZE = 30;
const int MAX_MARK_SIZE = 11;
const char objects[][MAX_WORD_SIZE] = { "kola","sklad","dqdo","prezident","kuche" };
const char subjects[][MAX_WORD_SIZE] = { "mladej","kotka","mutra","dete","slon" };
const char exclamations[][MAX_WORD_SIZE] = { "SHOK","Skandal","POTRES","Palna Glupost","Nevijdano do sega" };
const char actions[][MAX_WORD_SIZE] = { "prebi","vzrivi","precakva","ograbva","prodava" };

void myStrCopy(char* str1, const char* str2) {
	while (*str2) {
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1 = '\0';
}

char* generateArr(const char* word) {
	int length = strlen(word);
	char* arr = new (nothrow) char[length + 1];
	if (!arr) {
		return nullptr;
	}
	myStrCopy(arr, word);
	return arr;
}

int findRandomIndex() {
	return rand() % COL;
}

void outputArr(char** arr, int rows) {
	for (int i = 0; i < rows; i++)
	{
		cout << arr[i];
		if (i != 0) {
			cout << " ";
		}
	}
	cout << endl;
}

void clearMatrixByRows(char** matrix, int rows) {
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

char** allocMatrixByRows(int rows, char action[], char object[], char subject[], char exclamination[], char marks[]) {
	char** matrix = new(nothrow) char* [rows];
	if (!matrix) return matrix;

	int columns;
	for (int i = 0; i < rows; ++i) {
		if (i == 0) {
			columns = strlen(exclamination) + 1;
		}
		else if (i == 1) {
			columns = strlen(marks) + 1;
		}
		else if (i == 2) {
			columns = strlen(subject) + 1;
		}
		else if (i == 3) {
			columns = strlen(action) + 1;
		}
		else if (i == 4) {
			columns = strlen(object) + 1;
		}
		matrix[i] = new(nothrow) char[columns];
		if (!matrix[i]) {
			clearMatrixByRows(matrix, i);
			return nullptr;
		}
	}
	return matrix;
}

void fillArr(char** arr, int rows, char action[], char object[], char subject[], char exclamination[], char marks[]) {
	myStrCopy(arr[0], exclamination);
	myStrCopy(arr[1], marks);
	myStrCopy(arr[2], subject);
	myStrCopy(arr[3], action);
	myStrCopy(arr[4], object);
}

int main() {
	int n, length, index;
	cin >> n;
	srand(time(NULL));

	int count = 0;
	for (int i = 0; i < n; i++)
	{
		index = findRandomIndex();
		char* action = generateArr(actions[index]);
		index = findRandomIndex();
		char* object = generateArr(objects[index]);
		index = findRandomIndex();
		char* subject = generateArr(subjects[index]);
		index = findRandomIndex();
		char* exclamination = generateArr(exclamations[index]);

		int countOfMarks = (rand() % 8) + 3; //брой удивителни
		char* marks = new (nothrow) char[countOfMarks + 1];
		if (!action || !object || !subject || !exclamination || !marks) {
			cout << "No enough memory";
			return 0;
		}

		for (int i = 0; i < countOfMarks; i++)
		{
			marks[i] = '!';
		}
		marks[countOfMarks] = '\0';

		char** arr = allocMatrixByRows(WORDS, action, object, subject, exclamination, marks);
		if (!arr) {
			cout << "No enough memory" << endl;
		}
		else {
			fillArr(arr, WORDS, action, object, subject, exclamination, marks);
			delete[] action;
			delete[] object;
			delete[] subject;
			delete[] exclamination;
			delete[] marks;

			outputArr(arr, WORDS);
			clearMatrixByRows(arr, WORDS);
		}
	}
	return 0;
}