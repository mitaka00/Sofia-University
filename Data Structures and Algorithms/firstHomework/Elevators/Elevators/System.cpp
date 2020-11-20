#include <iostream>
#include <string>
#include <sstream>

#include "System.h"

using string = std::string;

const double eps = 0.01;
const char* fileName = "input.txt";

System::System() {
	std::cout << "Start\n";

	if (readFile()) {
		currentSeconds = 0;
	}
	else {
		std::cout << "There is no input.txt file.\n";
	}
}

bool System::readFile()
{
	std::ifstream in(fileName);

	if (!in) {
		return false;
	}


	int firstElevatorCapacity, secondElevatorCapacity, requestsCount;
	in >> floors >> firstElevatorCapacity >> secondElevatorCapacity >> requestsCount;
	firstElevator.setCapacity(firstElevatorCapacity);
	firstElevator.setMaxFloor(floors);
	secondElevator.setCapacity(secondElevatorCapacity);
	secondElevator.setMaxFloor(floors);

	for (int i = 0; i < requestsCount; i++)
	{
		request currentRequest;
		currentRequest.readRequest(in);
		currentRequest.done = false;
		requests.push_back(currentRequest);
	}

	return true;
}

System& System::i()
{
	static System instance;
	return instance;
}

System::~System()
{
	std::cout << "Have a nice day\n";
}

void System::run()
{
	std::list<request>::iterator firstIt = requests.begin();
	std::list<request>::iterator secondIt = requests.begin();
	bool isPrintedFirst = false;
	bool isPrintedSecond = false;
	while (!requests.empty()) {
		secondIt = firstIt;
		secondIt++;

		/*if (!isPrintedFirst && firstElevator.checkToOpen()) {
			std::cout << "S " << currentSeconds << " " << firstElevator.getCurrentFloor() << " " << firstElevator.getPrevDir() << std::endl;
			firstElevator.removePeople();

			isPrintedFirst = true;
		}
		if (!isPrintedSecond && secondElevator.checkToOpen()) {
			std::cout << "L " << currentSeconds << " " << secondElevator.getCurrentFloor() << " " << secondElevator.getPrevDir() << std::endl;
			secondElevator.removePeople();

			isPrintedSecond = true;
		}*/
		
		if ((*firstIt).name == "call" && (*firstIt).time <= currentSeconds) {
			if (!(*firstIt).done) {
				double firstDistance, secondDistance;
				firstDistance = firstElevator.distanceBetweenFloor((*firstIt).dir, (*firstIt).floor);
				secondDistance = secondElevator.distanceBetweenFloor((*firstIt).dir, (*firstIt).floor);

				if ((firstDistance != -1 && secondDistance == -1) || (firstDistance != -1 && secondDistance != -1 && firstDistance <= secondDistance)) {
					firstElevator.pushCall((*firstIt).floor, (*firstIt).dir);
					(*firstIt).done = true;
				}
				else if ((firstDistance == -1 && secondDistance != -1) || (firstDistance != -1 && secondDistance != -1 && firstDistance > secondDistance)) {
					secondElevator.pushCall((*firstIt).floor, (*firstIt).dir);
					(*firstIt).done = true;
				}
			}
		}
		else if ((*firstIt).name == "go" && (*firstIt).time <= currentSeconds ) {
			std::list<request>::iterator prevIt = --firstIt;
			firstIt++;
			if (abs(firstElevator.getCurrentFloor() - (*prevIt).floor) < eps && firstElevator.contain((*prevIt).floor)) {
				if (firstElevator.push((*firstIt).floor)) {
					if (secondIt != requests.end()) {
						firstIt = requests.erase(prevIt, secondIt);
					}
					else {
						requests.pop_back();
						requests.pop_back();
					}
					secondIt = firstIt;
				}
				else {
					(*prevIt).done = false;
				}
			}
			else if (abs(secondElevator.getCurrentFloor() - (*prevIt).floor) < eps && secondElevator.contain((*prevIt).floor)) {
				if (secondElevator.push((*firstIt).floor)) {
					if (secondIt != requests.end()) {
						firstIt = requests.erase(prevIt, secondIt);
					}
					else {
						requests.pop_back();
						requests.pop_back();
					}
					secondIt = firstIt;
				}
				else {
					(*prevIt).done = false;
				}
			}
		}
		else {
			isPrintedFirst = false;
			isPrintedSecond = false;
			firstElevator.removeCurrentFloorFromStops();
			secondElevator.removeCurrentFloorFromStops();

			firstElevator.makeStep(0.2);
			secondElevator.makeStep(0.2);
			currentSeconds++;

			if (firstElevator.checkToOpen()) {
				std::cout << "S " << currentSeconds << " " << firstElevator.getCurrentFloor() << " " << firstElevator.getPrevDir() << std::endl;
				firstElevator.removePeople();
			}
			if (secondElevator.checkToOpen()) {
				std::cout << "L " << currentSeconds << " " << secondElevator.getCurrentFloor() << " " << secondElevator.getPrevDir() << std::endl;
				secondElevator.removePeople();
			}
			firstIt = requests.begin();
			secondIt = requests.begin();
		}

		
		if (secondIt != requests.end()) {
			firstIt = secondIt;
		}
		else {
			firstIt = requests.begin();
			
			isPrintedFirst = false;
			isPrintedSecond = false;

			firstElevator.removeCurrentFloorFromStops();
			secondElevator.removeCurrentFloorFromStops();

			firstElevator.makeStep(0.2);
			secondElevator.makeStep(0.2);
			currentSeconds++;

			if (firstElevator.checkToOpen()) {
				std::cout << "S " << currentSeconds << " " << firstElevator.getCurrentFloor() << " " << firstElevator.getPrevDir() << std::endl;
				firstElevator.removePeople();
			}
			if (secondElevator.checkToOpen()) {
				std::cout << "L " << currentSeconds << " " << secondElevator.getCurrentFloor() << " " << secondElevator.getPrevDir() << std::endl;
				secondElevator.removePeople();
			}
		}
		
	}

	while (!firstElevator.isFinished() || !secondElevator.isFinished()) {
		if (firstElevator.checkToOpen()) {
			std::cout << "S " << currentSeconds << " " << firstElevator.getCurrentFloor() << " " << firstElevator.getPrevDir() << std::endl;
			firstElevator.removeCurrentFloorFromStops();
			firstElevator.removePeople();
			
		}
		if (secondElevator.checkToOpen()) {
			std::cout << "L " << currentSeconds << " " << secondElevator.getCurrentFloor() << " " << secondElevator.getPrevDir() << std::endl;
			secondElevator.removeCurrentFloorFromStops();
			secondElevator.removePeople();
		}

		currentSeconds++;
		firstElevator.makeStep(0.2);
		secondElevator.makeStep(0.2);
	}
}
void System::request::readRequest(std::ifstream& in)
{
	in >> this->name;

	if (this->name == "call") {
		in >> this->dir;
	}

	in >> this->floor;
	in >> this->time;
}
