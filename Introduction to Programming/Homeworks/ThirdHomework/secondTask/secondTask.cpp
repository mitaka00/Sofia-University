#include <iostream>
using namespace std;
int main() {
	int n;

	cout << "n= ";
	cin >> n;

	//Проверка на вход
	if (!cin || n < 1 || n>31) {
		cout << "Invalid input";
		return 0;
	}

	unsigned int buffer=0;
	int lastUsingNum;
	int oneCounter = 0;

	//Въвеждане на входни данни и броене на единиците
	for (int i = 0; i < n; i++)
	{
		int input;
		cin >> input;

		if (i == 0) {
			lastUsingNum = input;
			unsigned int mask = 1 << 31;
			buffer = 1;
		}
		else {
			if (input > lastUsingNum) {
				lastUsingNum = input;

				buffer = buffer << 1;

				unsigned int mask = 1;
				buffer = buffer | mask;

				oneCounter++;
			}
			else {
				buffer = buffer << 1;
			}
		}

	}

	//Броене на нулите в лява и дясна позиция спрямо средната единица
	int leftSideCounter = 0;
	int rightSideCounter = 0;
	int tokenOneCounter = 0;
	for (int i = 0; i < n; i++)
	{
		int currentNum = (buffer & 1);
		buffer = buffer >> 1;

		if (tokenOneCounter <= oneCounter / 2) {
			if (currentNum == 1) {
				tokenOneCounter++;
			}
			else {
				rightSideCounter++;
			}			
		}
		else {
			if (currentNum == 0) {
				leftSideCounter++;
			}
		}
	}

	//отпечатване на резултат
	if (leftSideCounter > rightSideCounter) {
		cout << "Left side: " << leftSideCounter;
	}
	else if (rightSideCounter > leftSideCounter) {
		cout << "Right side: " << rightSideCounter;
	}
	else {
		cout << "Both sides: " << rightSideCounter;
	}

	return 0;
}