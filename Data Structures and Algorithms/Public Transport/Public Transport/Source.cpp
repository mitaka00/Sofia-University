#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

const char* fileName = "input.txt";

struct Bus {
	int number;
	std::vector<std::string> stops;
};

struct Stop {
	std::string name;
	std::map<int, std::vector<int>> schedule;
};


void readStops(std::vector<Stop*>& stops, std::ifstream& in) {
	int count,busCount,scheduleCount,busNumber,currentMinutes;
	in >> count;
	stops.reserve(count);

	for (int i = 0; i < count; i++)
	{
		stops.push_back(new Stop());
		in >> stops[i]->name;
		in >> busCount;
		for (int j = 0; j < busCount; j++)
		{
			in >> busNumber;
			in >> scheduleCount;

			stops[i]->schedule[busNumber].reserve(scheduleCount);
			for (int v = 0; v < scheduleCount; v++)
			{
				in >> currentMinutes;
				stops[i]->schedule[busNumber].push_back(currentMinutes);
			}
		}
	}
}

void readBusses(std::map<int, std::vector<std::string>>& busses, std::ifstream& in) {
	int count,number,stopsCount;
	std::string stop;

	in >> count;
	for (int i = 0; i < count; i++)
	{
		in >> number;
		in >> stopsCount;
		busses[number].reserve(stopsCount);

		for (int j = 0; j < stopsCount; j++)
		{
			in >> stop;
			busses[number].push_back(stop);
		}
	}
}

bool readFile(std::map<int, std::vector<std::string>>& busses, std::vector<Stop*>& stops) {
	std::ifstream in(fileName);
	if (!in) {
		return false;
	}

	readStops(stops, in);
	readBusses(busses, in);

	return true;
}

int main() {
	std::map<int,std::vector<std::string>> busses;
	std::vector<Stop*> stops;

	if (!readFile(busses, stops)) {
		std::cout << "No file with name " << fileName;
		return 0;
	}



	return 0;
}