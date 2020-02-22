#include <iostream>
using namespace std;

int main() {
	int n;
	int number = 1;
	int count = 0;

	cout << "n= ";
	cin >> n;

	while (count < n) {
		int token = number;

		//ѕроверка дали числото се дели само на 2,3,5
		while (true) {
			if (token % 2 == 0) {
				token /= 2;
			}
			else if (token % 3 == 0) {
				token /= 3;
			}
			else if (token % 5 == 0) {
				token /= 5;
			}
			else {
				if (token == 1) {
					cout << number<<" ";
					count++;
					break;
				}
				else {
					break;
				}
			}
		}

		number++;
	}

	return 0;
}