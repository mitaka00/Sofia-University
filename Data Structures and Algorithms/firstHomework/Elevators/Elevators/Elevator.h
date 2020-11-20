#pragma once
#include <iostream>
#include <string>
#include <forward_list>
#include <vector>
#include <stack>

class Elevator
{
public:
	Elevator();
	bool push(const double& floor);
	void pushCall(const int floor,const std::string& currentDir);
	void removeCurrentFloorFromStops();
	void removePeople();
	void makeStep(const double step);

	bool checkToOpen();
	bool contain(const double& floor);
	bool isFull() const { return peopleCount == capacity; };
	bool isEmpty() const { return people.empty(); };
	bool isFinished() const { return stops.empty(); };

	double distanceBetweenFloor(const std::string& inputDir,const int inputFloor);

	void setCapacity(const int capacity) { this->capacity = capacity; };
	void setMaxFloor(const int maxFloor) { this->maxFloor = maxFloor; };
	void setDir(const std::string& dir) { this->dir = dir; };

	const double getCurrentFloor() const { return currentFloor; };
	const std::string getPrevDir() const { return prevDir; };
private:
	std::string dir, prevDir;
	double currentFloor,maxFloor;
	int capacity, peopleCount,stopsCount ,targetFloor;
	std::forward_list<int> stops;   //stops
	std::forward_list<int> people; //floor for each people in the elevator
};

