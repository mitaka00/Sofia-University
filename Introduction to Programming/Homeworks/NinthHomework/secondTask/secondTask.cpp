#include <iostream>
#include <cstdlib>
using namespace std;

const int EXT_LENGTH = 10;
const int EXT_COUNT = 20;

int myStrCmp(const char* str1,const char* str2)
{
	while (*str1 && *str1 == *str2)
	{
		++str1;
		++str2;
	}
	return *str1 - *str2;
}

void myStrCopy(char* str1,const char* str2) {
	while (*str2) {
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1 = '\0';
}

void addExtension(char* currentExt,char arr[][EXT_LENGTH],int& counter) {
	char token[2][EXT_LENGTH];
	int rowCount = 0, colCount = 0;
	bool checked = false;

	int length = strlen(currentExt);
	for (int i = 0; i < length; i++)
	{
		while (currentExt[i] >= 'a' && currentExt[i] <= 'z' && i < length) {
			token[rowCount][colCount] = currentExt[i];
			colCount++;
			i++;
			checked = true;
		}

		if (checked == true) {
			token[rowCount][colCount] = '\0';
			rowCount++;
			colCount = 0;
			checked = false;
		}
	}
	

	if (rowCount == 1) {
		myStrCopy(arr[counter], token[0]);
	}
	else if (rowCount == 2) {
		//Проверка за .enc дали е на първо или второ място
		if (myStrCmp(token[0], "enc\0") == 0) {
			myStrCopy(arr[counter], token[1]);
		}
		else {
			myStrCopy(arr[counter], token[0]);
		}
	}
}

int main() {
	int n,counter=0;
	char currentExtension[EXT_LENGTH];
	char extensions[EXT_COUNT][EXT_LENGTH];
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cout << "Enter file extension: ";
		cin.ignore();
		cin.getline(currentExtension, EXT_LENGTH);
		addExtension(currentExtension, extensions,counter);
		cout << endl;
	}

	//Втората част от задачата не е направена

	return 0;
}
