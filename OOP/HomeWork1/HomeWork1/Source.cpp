#include <iostream>
#include "Matrix.h"

int main() {
	Matrix matrix1("matrix1", 2, 2);
	Matrix matrix2("matrix2", 2, 2);
	int count = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			matrix2.setIndex(i, j, count);
			count++;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			matrix1.setIndex(i, j, count);
			count++;
		}
	}

	std::cout << matrix1<<std::endl<<matrix1.calcDeterm()<<std::endl;
	std::cout << matrix2 << std::endl << matrix2.calcDeterm()<<std::endl;
	std::cout << ~matrix1<<std::endl;
	std::cout << matrix1 << std::endl << matrix1.calcDeterm() << std::endl;
	std::cout << matrix1*2 << std::endl << std::endl;
	return 0;
}