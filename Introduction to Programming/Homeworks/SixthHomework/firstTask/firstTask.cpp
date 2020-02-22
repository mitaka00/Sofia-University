#include <iostream>
using namespace std;

const int MAX_LENGTH = 100;

void fillMatrx(int arr[][MAX_LENGTH],const int row,const int col) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> arr[i][j];
		}
	}
}

long findRowResult(int arr[][MAX_LENGTH], const int row, const int col) {
	long result = 1;
	for (int j = 0; j < col; j++)
	{
		result *= arr[row][j];
	}

	return result;
}

long findColResult(int arr[][MAX_LENGTH], const int row, const int col) {
	long result = 1;
	for (int i = 0; i < row; i++)
	{
		result *= arr[i][col];
	}

	return result;
}

void printResult(int arr[][MAX_LENGTH], const int row, const int col) {
	long rowResult = 1;
	long colResult = 1;
	bool isEqualResults = false;

	for (int i = 0; i < row; i++)
	{
		rowResult = findRowResult(arr, i, col);

		for (int j = 0; j < col; j++)
		{
			colResult = findColResult(arr, row, j);
			
			if (rowResult == colResult) {
				cout << i << ", " << j << " " << endl; 
				isEqualResults = true;
			}

			colResult = 1;
		}
		rowResult = 1;		
	}

	if (!isEqualResults) {
		cout << "No match";
	}
}

int main() {
	int row, col;
	cin >> row >> col;

	if (!cin || row<0 || col<0 || row>MAX_LENGTH || col>MAX_LENGTH) {
		cout << "Invalin input";
		return 0;
	}

	int arr[MAX_LENGTH][MAX_LENGTH];
	fillMatrx(arr, row, col);

	printResult(arr, row, col);

	return 0;

}