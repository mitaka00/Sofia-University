#include <iostream>
#include <fstream>

#include "Star.h"
const int MAX_NAME_LENGTH = 32;
const int MAX_STARS = 64;

#include "Spacecraft.h"
#include "Vector.h"

int main() {
	/*
	Code for Stars (first task)

	Star stars[MAX_STARS];
	char fileName[MAX_NAME_LENGTH];

	std::cout << "Enter file name:";
	std::cin >> fileName;

	int count=readAllStarsFromFile(fileName, stars);

	if (count == -1) {
		return -1;
	}

	double closestDistance;
	int index = getClosesIndex(stars, count, closestDistance);

	if (writeInFile(fileName, stars[index], closestDistance)) {
		std::cout << "Successfully appended result!" << std::endl;
	}
	**/


	/*
	Spacecraft test(2010, "Apollo 1");
	std::ofstream out("database.bin", std::ios::binary);
	if (!out) {
		std::cout << "error";
		return -1;
	}

	test.serialize(out);

	out.close();
	*/

	//Code for Spacecrafts (secondTask)
	bool readFromTextFile(const char* fileName, Vector& vector);
	bool writeInBinaryFile(const char* fileName, Vector& vector);
	bool readFromBinaryFile(const char* fileName, Vector& vector);

	Vector vector;
	if (!readFromTextFile("database.txt", vector)) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	if (!writeInBinaryFile("database.bin", vector)) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	Vector newVector;
	if (!readFromBinaryFile("database.bin", newVector)) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	std::cout << "Original vector:" << std::endl << vector << std::endl << std::endl;
	std::cout << "Vector from the database:" << std::endl << newVector << std::endl;

	return 0;
}

bool readFromTextFile(const char* fileName, Vector& vector) {
	std::ifstream in(fileName);
	if (!in) {
		return false;
	}

	while (!in.eof()) {
		int year;
		char name[MAX_NAME_LENGTH];
		in >> year;
		in.ignore();
		in.getline(name, MAX_NAME_LENGTH);
		vector.push_back(Spacecraft(year,name));
	}

	in.close();
	return true;
}

bool writeInBinaryFile(const char* fileName, Vector& vector) {
	std::ofstream out(fileName, std::ios::binary);
	if (!out) {
		return false;
	}

	vector.serialize(out);

	out.close();
	return true;
}

bool readFromBinaryFile(const char* fileName, Vector& vector) {
	std::ifstream in(fileName, std::ios::binary);
	if (!in) {
		return false;
	}

	vector.deserialize(in);

	in.close();
	return true;
}