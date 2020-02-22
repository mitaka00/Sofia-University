#include <iostream>
using namespace std;

bool checkPrimeNumber(int num) {
	if (num < 2) {
		return false;
	}

	if (num % 2 == 0) {
		if (num == 2) {
			return true;
		}
		else {
			return false;
		}
	}

	for (int i = 3; i <= num / 2; i+=2)
	{
		if (num % i == 0)
		{
			return false;
		}
	}

	return true;
}

int main() {
	unsigned int input;
	cin >> input;

	if (!input) {
		cout << "Invalid input";
		return 0;
	}

	if (input % 2 != 0) {
		cout << "Are you joking with me, Euler? This number is not even!"<<endl;
		return 0;
	}

	for (int firstNum = 2; firstNum <= input/2; firstNum++)
	{
		bool isFirstNumberPrime = checkPrimeNumber(firstNum);

		if (isFirstNumberPrime){ 
			for (int secondNum = firstNum; secondNum <= input; secondNum++)
			{
				bool isSecondNumberPrime = checkPrimeNumber(secondNum);

				if (isSecondNumberPrime && firstNum + secondNum == input) {
					cout << "(" << firstNum << ", " << secondNum << ") ";
					break;
				}
			}			
		}
	}
	return 0;
}

