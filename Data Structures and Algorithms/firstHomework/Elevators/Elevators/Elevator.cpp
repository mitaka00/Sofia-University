#include "Elevator.h"

const double eps = 0.01;
Elevator::Elevator()
{
	dir = "";
	currentFloor = 1;
	targetFloor = 0;
	peopleCount = 0;
	stopsCount = 0;
}
bool Elevator::push(const double& floor)
{
	if (isFull() ) {
		return false;
	}
	
	if ((floor > currentFloor && dir == "down" && !abs(targetFloor-currentFloor)<eps) || (floor < currentFloor && dir == "up" && !abs(targetFloor - currentFloor) < eps)) {
		return false;
	}
	people.push_front(floor);
	if (floor > currentFloor) {
		pushCall(floor, "up");
	}
	else {
		pushCall(floor, "down");
	}
	peopleCount++;

	return true;
}

void Elevator::pushCall(const int floor,const std::string& currentDir)
{
	if (!contain(floor)) {
		stops.push_front(floor);
		stopsCount++;
		if (dir == "") {
			targetFloor = floor;
			if (floor < currentFloor) {
				dir = "down";
			}
			else {
				dir = "up";
			}
		}
		else {
			dir = currentDir;
			if (dir == "up" && targetFloor < floor) {
				targetFloor = floor;
			}
			if (dir == "down" && targetFloor > floor) {
				targetFloor = floor;
			}
		}
		
	}
}

void Elevator::removePeople()
{
	std::forward_list<int>::iterator prev = people.before_begin();
	for (std::forward_list<int>::iterator it = people.begin(); it != people.end(); )
	{
		if (abs(*it-currentFloor)<eps)
		{
			it = people.erase_after(prev);
			peopleCount--;
		}
		else
		{
			prev = it;
			++it;
		}
	}
}

void Elevator::removeCurrentFloorFromStops()
{
	std::forward_list<int>::iterator prev = stops.before_begin();
	for (std::forward_list<int>::iterator it = stops.begin(); it != stops.end(); )
	{
		if (abs(*it - currentFloor) < eps)
		{
			it = stops.erase_after(prev);
			stopsCount--;
			break;
		}
		else
		{
			prev = it;
			++it;
		}
	}

	if (stops.empty()) {
		dir = "";
		targetFloor = 0;
	}
}

void Elevator::makeStep(const double step)
{
	prevDir = dir;
	if (dir == "up") {
		currentFloor += step;
	}
	else if (dir == "down") {
		currentFloor -= step;
	}
	
	if (abs(currentFloor-maxFloor)<eps) {
		dir = "";
		targetFloor = 0;
	}

	if (abs(currentFloor) < eps) {
		dir = "";
		targetFloor = 0;
	}
}

bool Elevator::checkToOpen()
{
	if (contain(currentFloor)) {
		return true;
	}

	return false;
}

double Elevator::distanceBetweenFloor(const std::string& inputDir, const int inputFloor)
{
	if (dir == "") {
		return abs(inputFloor - currentFloor);
	}
	else if (inputDir == dir) {
		if (dir == "up" && (abs(inputFloor-currentFloor)<eps || inputFloor>currentFloor) && (targetFloor==0 || targetFloor>=inputFloor)) {
			return inputFloor - currentFloor;
		}
		else if (dir == "down" && (abs(inputFloor - currentFloor) < eps || inputFloor < currentFloor) && (targetFloor == 0 || targetFloor <= inputFloor)) {
			return currentFloor - inputFloor;
		}
	}
	
	return -1;
}
bool Elevator::contain(const double& floor)
{
	if (stops.empty()) {
		return false;
	}
	std::forward_list<int>::iterator prev = stops.before_begin();
	for (std::forward_list<int>::iterator it = stops.begin(); it != stops.end(); ++it)
	{
		if (abs(*it - floor) < eps)
		{
			return true;
		}
	}
	return false;
}
