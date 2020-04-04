#pragma once

#include <fstream>
struct Star
{
	double x;
	double y;
	double z;
};

void readStarFromFile(std::ifstream & in, Star& star);

int readAllStarsFromFile(const char* fileName, Star* stars);

double calcDistance(const Star& star);

int getClosesIndex(const Star* stars, const int length, double& closestDistance);

bool writeInFile(const char* fileName, Star star, const double closestDistance);

