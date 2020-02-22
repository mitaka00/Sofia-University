#include <iostream>
using namespace std;

const int MAX_SIZE = 1024; //1кб има 1024 байта и 1мб има 1024кб  1024 * 1024
const int MAX_WORDS = 1024;
const int MAX_WORD_LENGTH = 64;

int myStrLen(const char* text) {
	int counter = 0;
	while (*text) {
		text++;
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
	*str1 = '\0';
}

int myStrCmp(const char* str1, const char* str2) {
	while (*str1 && *str1 == *str2) {
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

inline bool isLetter(char letter) {
	if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') || letter=='-') {
		return true;
	}
	else {
		return false;
	}
}

int findWordsCount(char* text) {
	int counter = 0;
	while (*text) {
		while (*text && !isLetter(*text)) {
			text++;
		}

		if (*text) {
			counter++;
		}

		while (isLetter(*text)) {
			text++;
		}
	}

	return counter;
}

int include(char matrix[][MAX_WORD_LENGTH], int length, char* buffer) {
	for (int i = 0; i < length; i++)
	{
		if (myStrCmp(matrix[i], buffer) == 0) {
			return i+1;
		}
	}

	return false;
}

void addCount(char matrix[][MAX_WORD_LENGTH], int length, char* buffer, int wordCount[]) {
	int index = include(matrix, length, buffer) - 1;
	wordCount[index] += 1;
}

void outputWords(char matrix[][MAX_WORD_LENGTH], int length, int wordCount[]) {
	for (int i = 0; i < length; i++)
	{
		cout << matrix[i] << " -> " << wordCount[i] << endl;
	}
}

void sortWords(char matrix[][MAX_WORD_LENGTH], int length, int wordCount[]) {
	bool changed = false;
	int sorted = 0;
	do {
		changed = false;
		
		for (int i = length-1; i > sorted; i--)
		{
			if (wordCount[i-1] < wordCount[i]) {
				changed = true;
				swap(wordCount[i - 1], wordCount[i]);
				swap(matrix[i - 1], matrix[i]);
			}
			else if (wordCount[i - 1] == wordCount[i]) {
				if (myStrCmp(matrix[i - 1], matrix[i]) > 0) {
					changed = true;
					swap(wordCount[i - 1], wordCount[i]);
					swap(matrix[i - 1], matrix[i]);
				}
			}
		}
		sorted++;

	} while (changed);
}

void filter(char* input) {
	while (*input) {
		if (*input == '#') {
			*input = '\0';
			input--;
		}
		input++;
	}
}

int main() {
	char input[MAX_SIZE];
	cin.getline(input, MAX_SIZE);

	filter(input);

	cout <<"All words: "<< findWordsCount(input) <<endl;

	char words[MAX_WORDS][MAX_WORD_LENGTH];
	int wordsCountArr[MAX_WORDS];
	int counter = 0;
	
	int inputLength = myStrLen(input);
	char buffer[MAX_WORD_LENGTH];
	int startedIndex = 0;


	for (int i = 0; i < inputLength; i++)
	{
		while (i < inputLength && !isLetter(input[i])) {
			i++;
		}

		startedIndex = i;
		while (isLetter(input[i])) {
			buffer[i - startedIndex] = input[i];
			i++;
		}
		buffer[i-startedIndex] = '\0';

		if (include(words, counter, buffer)) {
			addCount(words, counter, buffer,wordsCountArr);
		}
		else {
			myStrCpy(words[counter], buffer);
			wordsCountArr[counter] = 1;
			counter++;
		}

	}

	cout << "distinct words: " << counter << endl;

	sortWords(words, counter, wordsCountArr);
	outputWords(words, counter, wordsCountArr);

	return 0;
}