#include <iostream>
#include <cmath>
using namespace std;

long findMinNumber(long num1, long num2) {
	if (num1 > num2) {
		return num2;
	}
	else {
		return num1;
	}
}

long findMaxNumber(long num1, long num2) {
	if (num1 > num2) {
		return num1;
	}
	else {
		return num2;
	}
}

int returnDecimalDigit(char lastDigit)
{
	if (lastDigit >= '0' && lastDigit <= '9')
		return (int)lastDigit - '0';
	else
		return (int)lastDigit - 'A' + 10;
}

int sumOfDigitsInNumber(char *number, int numberSystem) {
	int len = strlen(number);
	int sum = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		if (returnDecimalDigit(number[i]) >= numberSystem)
		{
			cout<<"Invalid Number";
			return -1;
		}

		sum += returnDecimalDigit(number[i]);
	}

	return sum;
}

int NOD(long num1,long num2) {
	for (int i = findMinNumber(num1,num2); i >=1; i--)
	{
		if (num1 % i == 0 && num2 % i == 0) {
			return i;
		}
	}
}

long findPowOfNumber(long num1, long num2) {
	long result = num1;

	for (int i = 1; i < num2; i++)
	{
		result *= num1;
	}

	return result;
}

bool isNumberGreen(long number) {
	long token = number;
	unsigned long sum = 0;

	while (token > 0) {
		int lastDigit = token % 10;
		sum += lastDigit * lastDigit * lastDigit;
		
		token /= 10;
	}

	if (sum == number) {
		return true;
	}
	else {
		return false;
	}
}

long findSumOfGreenNumbers(long num1, long num2) {
	long sum = 0;
	for (int i = findMinNumber(num1,num2); i <=findMaxNumber(num1,num2) ; i++)
	{
		if (isNumberGreen(i)) {
			sum += i;
		}
	}

	return sum;
}

bool isNumberRed(long number) {
	long token = number;
	unsigned long sum = 0;

	while (token > 0) {
		int lastDigit = token % 10;
		sum += lastDigit;

		token /= 10;
	}

	if (number % sum == 0) {
		return true;
	}
	else {
		return false;
	}
}

long findSumOfRedNumbers(long num1, long num2) {
	long sum = 0;
	for (int i = findMinNumber(num1, num2); i <= findMaxNumber(num1, num2); i++)
	{
		if (isNumberRed(i)) {
			sum += i;
		}
	}

	return sum;
}

long findDSumOfGreenNumbersMinusSumOfRedNumbers(long num1, long num2) {
	return findSumOfGreenNumbers(num1, num2) - findSumOfRedNumbers(num1, num2);
}

double calculateTheCos(double x,int n) {
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	else {
		double sum = 1;
		int fakt = 2;
		for (int i = 2; i <= n; i++)
		{
			double currentNum=1.0;
			for (int j = 1; j <= fakt; j++)
			{
				currentNum = currentNum * x / j;
			}

			cout << currentNum<<endl;
			if (i % 2 == 0) {
				sum -= currentNum;
			}
			else {
				sum += currentNum;
			}			
			fakt += 2;
		}

		return sum;
	}
}

double calculateTheSin(double x, int n) {
	double cos = calculateTheCos(x,n);
	return sqrt(1 - cos * cos);
}

double calculateTheTg(double x, int n) {
	return sqrt(calculateTheSin(x, n) / calculateTheCos(x, n));
}

double calculateTheCotg(double x, int n) {
	return sqrt(calculateTheCos(x, n) / calculateTheSin(x, n));
}


int main() {
	char str[] = "723";
	cout << sumOfDigitsInNumber(str, 8);



	return 0;
}