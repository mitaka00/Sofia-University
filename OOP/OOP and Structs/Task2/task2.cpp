#include <iostream>
using namespace std;

struct Distance {
	double feet;
	double inches;
};

void printDistance(Distance input) {
	cout << input.feet << "'" << input.inches << "\"";
}

Distance addDistances(Distance firstDist, Distance secondDist) {
	Distance result;
	if (firstDist.inches + secondDist.inches >= 12) {
		result.inches = firstDist.inches + secondDist.inches - 12;
		result.feet = firstDist.feet + secondDist.feet + 1;
	}
	else {
		result.inches = firstDist.inches + secondDist.inches;
		result.feet = firstDist.feet + secondDist.feet;
	}

	return result;
}

int main() {
	Distance firstDist = { 1,6 };
	Distance secondDist = { 5,8 };
	Distance result = addDistances(firstDist, secondDist);

	printDistance(result);

	return 0;
}