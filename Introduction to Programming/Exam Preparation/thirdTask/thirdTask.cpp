#include <iostream>
using namespace std;
const int MAX_SIZE = 1024;

inline bool isLetter(char token) {
	if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z')) {
		return true;
	}
	return false;
}

int countWords(const char* input) {
	int counter = 0;
	while (*input) {
		while (*input && !isLetter(*input)) {
			input++;
		}

		if (*input) {
			counter++;
		}

		while (isLetter(*input)) {
			input++;
		}
	}

	return counter;
}

int myStrCmp(const char* str1, const char* str2) {
	while (*str1 && *str1 == *str2) {
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

int myStrLen(const char* str) {
	int counter = 0;
	while (*str) {
		str++;
		counter++;
	}
	return counter;
}

void myStrCpy(char* str1, const char* str2) {
	while (*str2) {
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1='\0';
}

bool contains(char** matrix,int wordsCounter, char* token) {
	for (int i = 0; i < wordsCounter; i++)
	{
		if (myStrCmp(matrix[i], token) == 0) {
			return true;
		}
	}
	return false;
}

void addCount(char** matrix,const int wordsCounter,int* arr,char* token) {
	for (int i = 0; i < wordsCounter; i++)
	{
		if (myStrCmp(matrix[i], token) == 0) {
			arr[i] += 1;
		}
	}
}

void clearMatrix(char** matrix, int row) {
	for (int i = 0; i <= row; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void outputMatrix(char** words,int wordsCounter,int* wordsCountArr) {
	for (int i = 0; i < wordsCounter; i++)
	{
		cout << words[i] << " -> " << wordsCountArr[i] << endl;
	}
}

void sortArrays(char** words, int wordsCounter, int* wordsCountArr) {
	int sorted = 0;
	bool checked = false;
	do{
		checked = false;
		for (int i = wordsCounter-1; i > sorted; i--)
		{
			if (wordsCountArr[i] > wordsCountArr[i - 1]) {
				swap(wordsCountArr[i], wordsCountArr[i - 1]);
				swap(words[i], words[i - 1]);
				checked = true;
			}
		}
		sorted++;
	} while (checked);
}

int main() {
	char input[MAX_SIZE];
	cin.getline(input, MAX_SIZE);

	int wordsCount = countWords(input);
	
	char** words = new(nothrow) char*[wordsCount];
	int* wordsCountArr = new(nothrow) int[MAX_SIZE];
	if (!words || !wordsCountArr) {
		cout << "Not enough memory!\n";
		return 1;
	}

	char buffer[MAX_SIZE];
	int wordsCounter = 0;
	int inputLength = strlen(input);
	int startedIndex = 0;

	for (int i = 0; i < inputLength; i++)
	{
		while ((i < inputLength) && !isLetter(input[i])) {
			i++;
		}

		if (i == inputLength) {
			break;
		}
		
		startedIndex = i;
		while ((i < inputLength)&&(isLetter(input[i]))) {
			i++;
		}

		for (int g = startedIndex; g < i; g++)
		{
			buffer[g - startedIndex] = input[g];
		}
		buffer[i - startedIndex] = '\0';
		bool checked = contains(words, wordsCounter, buffer);
		if (checked) {
			addCount(words, wordsCounter,wordsCountArr, buffer);
		}
		else {
			words[wordsCounter] = new(nothrow) char[myStrLen(buffer)+1];
			if (!words[wordsCounter]) {
				cout << "No enough memory";
				clearMatrix(words, wordsCounter);
				delete[] wordsCountArr;
				return 1;
			}

			myStrCpy(words[wordsCounter], buffer);
			wordsCountArr[wordsCounter] = 1;
			wordsCounter++;
		}
	}

	sortArrays(words, wordsCounter, wordsCountArr);

	outputMatrix(words, wordsCounter,wordsCountArr);
	
	return 0;
}