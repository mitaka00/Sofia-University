#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#include "Elevator.h"
class System
{
public:
	static System& i();

	System(const System&) = delete;
	void operator=(const System&) = delete;
	~System();

	void run();
private:
	System();

	struct request
	{
		std::string name;
		std::string dir;
		double floor;
		int time;
		bool done;

		void readRequest(std::ifstream& in);
	};

	int floors,currentSeconds;
	Elevator firstElevator, secondElevator;
	std::list<request> requests;

	bool readFile();
};

