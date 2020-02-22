#include <iostream>
using namespace std;
int main() {
	int number;
	cout << "n= ";
	cin >> number;

	if (!cin || number > 3000 || number < 0) {
		cout << "Invalid number";
	}
	else{
		int centCount = number / 1000;
		int hundCount = number / 100 % 10;
		int tenCount = number / 10 % 10;
		int lastDigitCount = number % 10;

		//Това за знаците за хилядните:
		for (int i = 0; i < centCount; i++)
		{
			cout << "M";
		}

		//Това са знаците за стотиците:
		if (hundCount <= 3) {
			for (int i = 0; i < hundCount; i++)
			{
				cout << "C";
			}
		}
		else if(hundCount==4){
			cout << "C";
		}
		else if (hundCount > 4 && hundCount < 9) {
			cout << "D";
			for (int i = 5; i < hundCount; i++)
			{
				cout << "C";
			}
		}
		else {
			cout << "CM";
		}

		//Това са знаците за десетиците:
		if (tenCount <= 3) {
			for (int i = 0; i < tenCount; i++)
			{
				cout << "X";
			}
		}
		else if (tenCount == 4) {
			cout << "XL";
		}
		else if (tenCount > 4 && tenCount < 9) {
			cout << "L";
			for (int i = 5; i < tenCount; i++)
			{
				cout << "X";
			}
		}
		else {
			cout << "XC";
		}

		//Това са знаците за Единиците:
		if (lastDigitCount <= 3) {
			for (int i = 0; i < lastDigitCount; i++)
			{
				cout << "I";
			}
		}
		else if (lastDigitCount == 4) {
			cout << "IV";
		}
		else if (lastDigitCount > 4 && lastDigitCount < 9) {
			cout << "V";
			for (int i = 5; i < lastDigitCount; i++)
			{
				cout << "I";
			}
		}
		else {
			cout << "IX";
		}
	}

	return 0;
}