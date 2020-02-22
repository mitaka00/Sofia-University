#include <iostream>
using namespace std;
const int PARAMS = 4;

void clearMatrix(int** matrix, int i) {
	for (int g = 0; g <= i; g++)
	{
		delete[] matrix[g];
	}
	delete[] matrix;
}

int** generateMatrix(int rows) {
	int** matrix = new (nothrow) int* [rows];
	if (!matrix) {
		return nullptr;
	}
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new (nothrow) int[PARAMS];
		if (!matrix[i]) {
			clearMatrix(matrix, i);
			return nullptr;
		}
	}
	return matrix;
}

void fillMatrix(int** matrix, int n) {
	int a, b, c;
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b >> c;
		matrix[i][0] = a;
		matrix[i][1] = b;
		matrix[i][2] = c;
		matrix[i][3] = 0; //Служи за проверка дали вече уравнението е принтирано
	}
}

bool checkIsSolution(int** matrix, int currentNum, int i) {
	int result = matrix[i][0] * currentNum * currentNum + matrix[i][1] * currentNum + matrix[i][2];
	if (result == 0) {
		return true;
	}
	return false;
}

void printResult(int** matrix, int n, int currentNum) {
	for (int i = 0; i < n; i++)
	{
		if (matrix[i][3] == 0 && checkIsSolution(matrix,currentNum,i)) {
			cout << matrix[i][0] << "*x^2 + " << matrix[i][1] << "*x + " << matrix[i][2] << endl;
			matrix[i][3] = 1;
		}
	}
}

int main() {
	int n;
	cin >> n;

	int** matrix = generateMatrix(n);
	if (!matrix) {
		cout << "No enough memory";
		return 0;
	}

	fillMatrix(matrix, n);

	int k,currentNum;
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		cin >> currentNum;
		printResult(matrix, n, currentNum);
	}

	clearMatrix(matrix, n);

	return 0;
}