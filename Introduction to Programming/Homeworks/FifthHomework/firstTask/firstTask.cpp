#include <iostream>
using namespace std;
const int MAX_LENGTH = 1000;

int main() {
	int n;
	cin >> n;

	if (!cin || n >= 1000) {
		cout << "Invalid input";
		return 0;
	}

	double arr[MAX_LENGTH];
	double input;

	for (int i = 0; i < n+1; i++)
	{
		cin >> input;
		arr[i] = input;
	}

	int proizvodna;
	cin >> proizvodna;
	for (int i = 0; i < proizvodna; i++)
	{
		for (int j = 0; j < n+1; j++)
		{
			arr[j] = arr[j] * (n - j);
		}

		n--;
	}

	if (n < 0) {
		cout << "0";
	}
	else {
		for (int i = 0; i <= n; i++)
		{
			if (i == n) {
				cout << arr[i];
			}
			else if (i == n - 1) {
				cout << arr[i] << "*X" << " + ";
			}
			else {
				cout << arr[i] << "*X^" << n - i << " + ";
			}
		}
	}
	return 0;
}