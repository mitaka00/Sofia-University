#include <iostream>
using namespace std;

struct ComplexNumber {
	double img;
	double real;
};

ComplexNumber addComplexnumber(ComplexNumber num1, ComplexNumber num2) {
	ComplexNumber result;
	result.img = num1.img + num2.img;
	result.real = num1.real + num2.real;
	return result;
}

void printComplexNumber(ComplexNumber number) {
	cout << number.img << "*i + " << number.real;
}
int main() {
	ComplexNumber number1 = { 1,2 };
	ComplexNumber number2 = { 3,4 };

	ComplexNumber result = addComplexnumber(number1, number2);
	printComplexNumber(result);


	return 0;
}