#include "Star.h"
#include <iostream>
#include <cmath>
#include <iomanip>


void readStarFromFile(std::ifstream& in, Star& star) {
	in >> star.x >> star.y >> star.z;
}

int readAllStarsFromFile(const char* fileName, Star* stars)
{
	std::ifstream in(fileName);
	if (!in) {
		std::cout << "File don't exist" << std::endl;
		return -1;
	}

	int numStars;
	in >> numStars;
	for (int i = 0; i < numStars; i++)
	{
		readStarFromFile(in, stars[i]);
	}

	in.close();

	return numStars;
}

double calcDistance(const Star& star)
{
	return sqrt((star.x * star.x) + (star.y * star.y) + (star.z * star.z));
}

int getClosesIndex(const Star* stars, const int length, double& closestDistance)
{
	double currentDistace;
	int index = 0;
	closestDistance = calcDistance(stars[0]);
	for (int i = 1; i < length; i++)
	{
		currentDistace = calcDistance(stars[i]);
		if (currentDistace < closestDistance) {
			closestDistance = currentDistace;
			index = i;
		}
	}

	return index;
}

bool writeInFile(const char* fileName, Star star, const double closestDistance)
{
	std::ofstream out(fileName, std::ios::app);
	if (!out) {
		std::cout << "Coulnt open file for writing!" << std::endl;
		return false;
	}

	out << std::endl <<"The closest star to us is located at ("
		<< star.x << ", " << star.y << ", " << star.z << ") that is "
		<< std::setprecision(2) << std::fixed << closestDistance << " lightyears away.";

	out.close();
	return true;
}

