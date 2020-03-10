#include <iostream>
using namespace std;

struct TimePeriod {
	int hours;
	int minutes;
	int seconds;
};

TimePeriod difference(TimePeriod firstTime, TimePeriod secondTime) {
	TimePeriod result;
	int resultSeconds = 0;

	int firstTimeSeconds = firstTime.hours * 3600 + firstTime.minutes * 60 + firstTime.seconds;
	int secondTimeSeconds = secondTime.hours * 3600 + secondTime.minutes * 60 + secondTime.seconds;

	if (firstTimeSeconds >= secondTimeSeconds) {
		resultSeconds = firstTimeSeconds - secondTimeSeconds;
	}
	else {
		resultSeconds = secondTimeSeconds - firstTimeSeconds;
	}

	result.hours = resultSeconds / 3600;
	result.minutes = resultSeconds /60;
	result.seconds = resultSeconds - result.hours * 3600 - result.minutes * 60;

	return result;
}

void printResult(TimePeriod time) {
	cout << time.hours << ":" << time.minutes << ":" << time.seconds;
}

int main() {
	TimePeriod firstTime= { 2,30,15 };
	TimePeriod secondTime = { 3,15,45 };

	TimePeriod result = difference(firstTime, secondTime);
	
	cout << "The difference between ";
	printResult(firstTime);
	cout << " and ";
	printResult(secondTime);
	cout << " is ";
	printResult(result);

	
	return 0;
}