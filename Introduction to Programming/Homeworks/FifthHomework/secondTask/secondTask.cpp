#include <iostream>
#include <stdlib.h> 
#include <time.h>
using namespace std;

const int MAX_LENGTH = 1000;
const int DEFAULT_LENGTH = 10;
const int DEFAULT_TRACE[DEFAULT_LENGTH] = { 1,0,0,1,1,1,1,0,1,0 };

bool checkPrimeNumber(int num) {
	if (num < 2) {
		return false;
	}

	if (num % 2 == 0) {
		if (num == 2) {
			return true;
		}
		else {
			return false;
		}
	}

	for (int i = 3; i <= num / 2; i += 2)
	{
		if (num % i == 0)
		{
			return false;
		}
	}

	return true;
}

int makeRandomTrace(int trace[]) {
	srand(time(NULL));
	int length = 10 + rand() % 990;

	for (int i = 0; i < length; i++)
	{
		trace[i] = rand() % 2;
	}

	return length;
}

void defineTrace(int trace[],int& traceLength) {
	if (traceLength == 0) {
		traceLength = DEFAULT_LENGTH;
		for (int i = 0; i < traceLength; i++)
		{
			trace[i] = DEFAULT_TRACE[i];
		}
	}
	else if (traceLength < 0) {
		traceLength = makeRandomTrace(trace);
	}
	else {
		for (int i = 0; i < traceLength; i++)
		{
			cin >> trace[i];
		}
	}
}

void findLongestDistance(const int trace[],const int traceLength, int& startingPositionForLongestDistance, int& longestDistance) {
	int currentDistance = 0;
	int platformCount = 1;
	int holeCount = 1;

	for (int i = 0; i < traceLength - 1; i++)
	{
		if (trace[i] == trace[i + 1] && trace[i] == 0) {
			holeCount++;
		}
		else if (trace[i] == trace[i + 1] && trace[i] == 1) {
			platformCount++;
		}
		else {
			holeCount = 1;
			platformCount = 1;
		}

		if (currentDistance == 0 && trace[i] == 1) {
			currentDistance = 1;
		}
		else if (currentDistance == 0 && trace[i] == 0) {
			currentDistance = 0;
		}
		else if (holeCount > 3) {
			currentDistance = 0;
		}
		else {
			currentDistance++;
		}

		if (i == traceLength - 2 && platformCount != 1) {
			currentDistance++;
		}
		if (longestDistance < currentDistance && trace[i] == 1) {
			longestDistance = currentDistance;
			startingPositionForLongestDistance = i + 1 - currentDistance;
			if (i == traceLength - 2 && trace[traceLength-1]==1) {
				startingPositionForLongestDistance++;
			}
		}
	}
}

void findLongestPlatform(const int trace[], const int traceLength, int& startingPositionForLongestPlatform, int& longestPlatform) {
	int platformCount = 0;
	int holeCount = 1;
	bool isPositionChecked = false;

	for (int i = 0; i < traceLength - 1; i++)
	{
		if (trace[i] == trace[i + 1] && trace[i] == 0) {
			holeCount++;
			isPositionChecked = false;
		}
		else if (trace[i] == trace[i + 1] && trace[i] == 1) {
			platformCount++;
		}
		else {
			if (trace[i] == 1) {
				platformCount += 1;
				holeCount = 0;				
			}
			else {
				platformCount = 0;
				holeCount = 1;	
				isPositionChecked = false;
			}
		}

		if (i == traceLength - 2 && trace[traceLength-1]==1) {
			platformCount++;
		}
		if (longestPlatform < platformCount) {
			longestPlatform = platformCount;
			if (!isPositionChecked) {
				startingPositionForLongestPlatform = i - platformCount + 1;
				isPositionChecked = true;
			}
			if (i == traceLength - 2) {
				startingPositionForLongestPlatform++;
			}
		}
	}
}

void findPrimeLengthPlatforms(const int trace[], const int traceLength, int primeStartingIndexes[], int& primeCount) {
	int platformCount = 0;
	int holeCount = 1;
	bool isPositionChecked = true;

	for (int i = 0; i < traceLength - 1; i++)
	{
		if (trace[i] == trace[i + 1] && trace[i] == 0) {
			holeCount++;
		}
		else if (trace[i] == trace[i + 1] && trace[i] == 1) {
			platformCount++;
		}
		else {
			if (trace[i] == 1) {
				platformCount += 1;
				holeCount = 0;
				isPositionChecked = false;
			}
			else {
				platformCount = 0;
				holeCount = 1;
				isPositionChecked = true;
			}
		}

		if (!isPositionChecked || (i==traceLength-2 && trace[i]==1)) {
			isPositionChecked = true;

			if (i == traceLength - 2 && trace[i+1]==1) {
				platformCount++;
			}
			if (platformCount > 1) {
				if (checkPrimeNumber(platformCount)) {
					primeStartingIndexes[primeCount] = platformCount;
					primeCount++;
				}

			}
		}
	}
}

void findMinimalCountPlatformsForAdding(const int trace[], const int traceLength,int& totalLengthOfAddedPlatforms,int& addedPlatformsCount) {
	int holeCount = 1;
	bool isChecked = false;

	for (int i = 0; i < traceLength - 1; i++)
	{
		if (trace[i] == trace[i + 1] && trace[i] == 0) {
			holeCount++;
		}
		else {
			isChecked = false;

			if (holeCount > 3) {
				addedPlatformsCount++;
				totalLengthOfAddedPlatforms += holeCount/3;
			}

			holeCount = 1;
		}		
	}
}

int main() {
	int traceLength;
	int trace[MAX_LENGTH];

	cin >> traceLength;

	defineTrace(trace, traceLength);

	//firstTask
	int longestDistance = 0;
	int startingPositionForLongestDistance=-1;
	findLongestDistance(trace, traceLength, startingPositionForLongestDistance, longestDistance);

	//secondTask
	int longestPlatform = 0;
	int startingPositionForLongestPlatform = -1;
	findLongestPlatform(trace, traceLength, startingPositionForLongestPlatform, longestPlatform);

	//thirdTask
	int primeCount = 0;
	int primeStartingIndexes[MAX_LENGTH];
	findPrimeLengthPlatforms(trace, traceLength, primeStartingIndexes, primeCount);

	//fourthTask
	int totalLengthOfAddedPlatofrms = 0;
	int minimalCountPlatformsForAdding = 0;
	findMinimalCountPlatformsForAdding(trace, traceLength,totalLengthOfAddedPlatofrms,minimalCountPlatformsForAdding);
	

	//Output
	if (startingPositionForLongestDistance == -1) {
		cout << "Mario can not jump" << endl;
	}
	else {
		cout << "Best starting position is " << startingPositionForLongestDistance << " and the run length is " << longestDistance << " steps." << endl;
	}

	if (startingPositionForLongestPlatform == -1) {
		cout << "No platforms" << endl;
	}
	else {
		cout << "Longest platform starts from position " << startingPositionForLongestPlatform << " and has length of " << longestPlatform << " steps." << endl;
	}

	if (primeCount == 0) {
		cout << "There are 0 prime-length platforms. Their lengths: 0" << endl;
	}
	else {
		cout << "There are " << primeCount << " prime-length platforms. Their lengths: ";
		for (int i = 0; i < primeCount; i++)
		{
			cout << primeStartingIndexes[i] << " ";
		}
		cout << endl;
	}

	if (minimalCountPlatformsForAdding == 0) {
		cout << "Mario needs  0 new platforms with total length 0." << endl;
	}
	else {
		cout << "Mario needs " << minimalCountPlatformsForAdding << " new platforms with total length " << totalLengthOfAddedPlatofrms << "." << endl;
	}
	

	return 0;
}