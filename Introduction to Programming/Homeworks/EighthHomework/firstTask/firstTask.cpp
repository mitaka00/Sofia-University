#include <iostream>
#include <new>
using namespace std;

void clearArr(int** arr, int rows) {
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

int** dynamicArr(int rows, int cols) {
	int** arr = new(nothrow) int* [rows];
	if (!arr) {
		return arr;
	}

	for (int i = 0; i < rows;  i++)
	{
		arr[i] = new(nothrow) int[cols];
		if (!arr[i]) {
			clearArr(arr, i);
			return nullptr;
		}
	}

	return arr;
}

void readArr(int** arr, int rows, int cols) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cin >> arr[i][j];
		}
	}
}

void showArr(int** arr, int rows, int cols) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

int sumRow(int** arr, int row, int cols) {
	int sum = 0;
	for (int i = 0; i < cols; i++)
	{
		sum += arr[row][i];
	}

	return sum;
}

void swapRow(int** arr, int firstRow, int secondRow, int cols) {
	for (int i = 0; i < cols; i++)
	{
		int x = arr[firstRow][i];
		arr[firstRow][i] = arr[secondRow][i];
		arr[secondRow][i] = x;
	}
}

void sortArr(int** arr, int rows, int cols) {
	bool changed = false;
	unsigned int sorted = 0;

	do {
		changed = false;
		for (int i = rows - 1; i > sorted; i--)
		{
			int firstSum = sumRow(arr, i, cols);
			int secondSum = sumRow(arr, i-1, cols);
			//cout << firstSum << " " << secondSum << endl;
			if (firstSum < secondSum) {
				swapRow(arr, i, i - 1,cols);
				changed = true;
			}
		}
		sorted++;
	} while (changed);
}

int main() {
	int n, m;
	cin >> n;
	cin >> m;

	int** arr = nullptr;
	arr = dynamicArr(n, m);
	if (!arr) {
		return 1;
	}

	readArr(arr, n, m);
	cout << "Arr: " << endl;
	showArr(arr, n, m);

	cout << "Sorted arr: " << endl;
	sortArr(arr, n, m);
	showArr(arr, n, m);

	clearArr(arr, n);

	return 0;
}