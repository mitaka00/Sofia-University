#include <iostream>
using namespace std;

int sumDigits(int number) {
	if (number == 0) {
		return 0;
	}

	return number % 10 + sumDigits(number/10);
}

int* generateArr(int n) {
	int* arr = new (nothrow) int[n];
	if (!arr) {
		return nullptr;
	}
	return arr;
}

int findMaxSum(int* arr, int n) {
	int sum = arr[0];
	for (int i = 1; i < n; i++)
	{
		if (sum < arr[i]) {
			sum = arr[i];
		}
	}
	return sum;
}

void clearMatrix(int** matrix, int i) {
	for (int g = 0; g <= i; g++)
	{
		delete[] matrix[g];
	}
	delete[] matrix;
}

int** generateMatrix(int rows, int cols) {
	int** matrix = new (nothrow) int* [rows+1];
	if (!matrix) {
		return nullptr;
	}
	for (int i = 0; i <= rows; i++)
	{
		matrix[i] = new (nothrow) int[cols];
		if (!matrix[i]) {
			clearMatrix(matrix, i);
			return nullptr;
		}
	}
	return matrix;
}

void fillArr(int* arr, int row) {
	for (int i = 0; i < row; i++)
	{
		arr[i] = 0;
	}
}

void fillMatrix(int** matrix, int rows, int cols) {
	for (int i = 0; i <= rows; i++)
	{
		for (int g = 0; g < cols; g++)
		{
			matrix[i][g] = 0;
		}
	}
}

void outputMatrix(int** matrix, int rows, int* cols) {
	for (int i = 0; i <= rows; i++)
	{
		cout << i << ":" << " ";
		int col = cols[i];
		for (int g = 0; g < col; g++)
		{
			cout << matrix[i][g] << " ";
		}
		cout << endl;
	}
}

int main() {
	int n;
	cin >> n;
	if (!cin || n < 0) {
		cout << "Invalid input";
		return 0;
	}

	int* numbers = generateArr(n);
	int* sums = generateArr(n);
	if (!numbers || !sums) {
		cout << "No enough memory";
		return 0;
	}

	for (int i = 0; i < n; i++)
	{
		int currentNum;
		cin >> currentNum;
		numbers[i] = currentNum;
		sums[i] = sumDigits(currentNum);
	}

	int maxSum = findMaxSum(sums, n);
	int** result = generateMatrix(maxSum, n);
	int* matrixRowLength = generateArr(maxSum+1);
	if (!result || !matrixRowLength) {
		cout << "No enough memory";
		return 0;
	}

	fillArr(matrixRowLength, maxSum+1);
	fillMatrix(result, maxSum, n);
	
	for (int i = 0; i < n; i++)
	{
		int currentNum = numbers[i];
		int currentRow = sums[i];
		int currentCol = matrixRowLength[currentRow];
		result[currentRow][currentCol] = currentNum;
		matrixRowLength[currentRow]+=1;
	}

	outputMatrix(result, maxSum, matrixRowLength);

	delete[] numbers;
	delete[] sums;
	clearMatrix(result, maxSum);
	delete[] matrixRowLength;

	return 0;
}