#include <iostream>
using namespace std;
int main() {
	unsigned int input;
	cout << "number= ";
	cin >> input;

	if (input / 100000000 < 1 || input / 100000000 >= 10) {
		cout << "Invalid input" << endl; //Проверка за 9 цифрено число
		return 0;
	}

	int secondDigit = input / 10000000 % 10;

	if (secondDigit > 7) {
		cout << "This card is a copy";
		return 0;
	}

	//Проверка за коса, очи и пол
	int gender,eyes,hair;

	if (secondDigit == 0) {
		gender = 0;
		eyes = 0;
		hair = 0;
	}
	else if (secondDigit % 2 == 0) {
		gender = 0;
		hair = 1;
		eyes = 0;
	}
	else {
		gender = 1;
		hair = 0;
		eyes = 0;
	}

	if (secondDigit >= 4) {
		eyes = 1;
	}


	int firstDigit = input / 100000000;
	int thirdDigit= input / 1000000 % 10;
	int fourthDigit = input / 100000 % 10;
	int fifthDigit = input / 10000 % 10;
	int sixthDigit = input / 1000 % 10;
	int seventhDigit = input / 100 % 10;
	int eighthDigit = input / 10 % 10;
	int lasthDigit = input % 10;

	//first Action
	unsigned int actions = (firstDigit + thirdDigit + fifthDigit + seventhDigit + lasthDigit) * (secondDigit + fourthDigit + sixthDigit + eighthDigit);

	//second Action
	if (hair == 1 && eyes == 1) {
		actions = (actions | 0xCAFE);
	}
	else if (hair == 0 && eyes == 0) {
		actions = (actions | 0xBABE);
	}
	else {
		actions = (actions | 0xC001);
	}

	//third Action
	if (gender == 1) {
		unsigned int mask = 0xC0DE;
		actions = (actions ^ mask);
	}
	else
	{
		unsigned int mask = 0xFACE;
		actions = (actions ^ mask);
	}

	const int MOVEBITS = 12;
	actions = (actions >> MOVEBITS);
	if (actions > 10) {
		actions = actions % abs(10);
	}

	cout << actions << endl;
	if (actions == lasthDigit) {
		cout << "Authentic";
	}
	else
	{
		cout << "Imitative";
	}
	return 0;
}