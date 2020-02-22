#include <iostream>
#include <cmath>
using namespace std;
int main() {
	int x1, y1, x2, y2, r1, r2;

	cout << "x1= ";
	cin >> x1;
	cout << "y1= ";
	cin >> y1;
	cout << "r1= ";
	cin >> r1;

	cout << "x2= ";
	cin >> x2;
	cout << "y2= ";
	cin >> y2;
	cout << "r2= ";
	cin >> r2;

	long distanceBetweenCentersSquared = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	long totalR1andR2Squared = (r1 + r2) * (r1 + r2);
	long subtractionR1andR2Squared = (r1 - r2) * (r1 - r2);

	if (distanceBetweenCentersSquared == 0 && r1==r2) {
		cout << "The circles are the same" << endl;
	}
	else if (distanceBetweenCentersSquared == subtractionR1andR2Squared || distanceBetweenCentersSquared == totalR1andR2Squared) {
		cout << "The circles are touching" << endl;
	}
	else if (distanceBetweenCentersSquared > totalR1andR2Squared) {
		cout << "No common points" << endl;	
	}
	else if (subtractionR1andR2Squared < distanceBetweenCentersSquared && distanceBetweenCentersSquared < totalR1andR2Squared) {
		cout << "The circles are crossing" << endl;
	}
	else {
		cout << "The smaller circle is in the bigger and they are no crossing" << endl;
	}
	return 0;
}