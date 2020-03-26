#include <iostream>
#include "Matrix.h"
#include "Vector.h"

int main() {
	Vector vector;
	char command;
	int param1,param2;
	char name[MAX_NAME_LENGTH];
	do {
		std::cin >> command;
		if (command == 'c') {
			std::cin >> param1 >> param2 >> name;
			Matrix matrix(name, param1, param2);
			int token;
			for (int i = 0; i < param1; i++)
			{
				for (int j = 0; j < param2; j++)
				{
					std::cin >> token;
					matrix.setIndex(i, j, token);
				}
			}
			vector.push_back(matrix);
		}
		else if (command == 'p') {
			std::cin >> name;
			int length = vector.size();
			for (int i = 0; i < length; i++)
			{
				if (strcmp(name, vector[i].getName()) == 0) {
					std::cout << vector[i] << std::endl;
				}
			}
		}
		else if (command == 'd') {
			std::cin >> name;
			int length = vector.size();
			for (int i = 0; i < length; i++)
			{
				if (strcmp(name, vector[i].getName()) == 0) {
					std::cout << vector[i].calcDeterm() << std::endl;
				}
			}
		}
		else if (command == 'a') {
			bool isReady = false;
			char secondName[MAX_NAME_LENGTH];
			std::cin >> name >> secondName;
			int length = vector.size();
			for (int i = 0; i < length; i++)
			{
				if (strcmp(name, vector[i].getName()) == 0) {
					for (int j=i+1  ; j < length; j++)
					{
						if (strcmp(secondName, vector[j].getName()) == 0) {
							vector.push_back(vector[i] + vector[j]);
							isReady = true;
							break;
						}
					}
					if (isReady) {
						break;
					}
				}
			}
		}
		else if (command == 'm') {
			bool isReady = false;
			char secondName[MAX_NAME_LENGTH];
			std::cin >> name >> secondName;
			int length = vector.size();
			for (int i = 0; i < length; i++)
			{
				if (strcmp(name, vector[i].getName()) == 0) {
					for (int j = i + 1; j < length; j++)
					{
						if (strcmp(secondName, vector[j].getName()) == 0) {
							vector.push_back(vector[i] * vector[j]);
							isReady = true;
							break;
						}
					}
					if (isReady) {
						break;
					}
				}
			}
		}
		else if (command == 's') {
			std::cin >> param1 >> name;
			int length = vector.size();
			for (int i = 0; i < length; i++)
			{
				if (strcmp(name, vector[i].getName()) == 0) {
					vector[i] *= param1;
				}
			}
		}
		else if (command == 't') {
			std::cin >> name;
			int length = vector.size();
			for (int i = 0; i < length; i++)
			{
				if (strcmp(name, vector[i].getName()) == 0) {
					vector[i] = ~vector[i];
				}
			}
		}

		std::cout << "New command" << std::endl;
	} while (command != 'q');


	return 0;
}