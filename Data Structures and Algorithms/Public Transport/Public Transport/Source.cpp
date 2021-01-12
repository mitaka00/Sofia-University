#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <map>

const char* fileName = "input.txt";

using Edge = std::pair < std::string, int >;
using Vertex = std::list< Edge >;
// This class represents a directed graph using 
// adjacency list representation 
class Graph
{
	int V; // No. of vertices 

	// In a weighted graph, we need to store vertex 
	// and weight pair for every edge 
	std::map<std::string,Vertex > adj;
	
public:
	void addEdge(const std::string& u,const std::string& v, int w);

	void shortestPath(int s);
};

void Graph::addEdge(const std::string& u, const std::string& v, int w)
{
	adj[u].push_back(make_pair(v, w));
}

struct Bus {
	int number;
	std::vector<std::string> stops;
};

struct Stop {
	std::string name;
	std::map<int, std::vector<int>> schedule;
};


void readStops2(std::vector<Stop*>& stops, std::ifstream& in) {
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

void readStops(std::map<std::string, std::map<int, std::vector<int>>>& stops, std::ifstream& in) {
	int count, busCount, scheduleCount, busNumber, currentMinutes;
	std::string name;

	in >> count;
	for (int i = 0; i < count; i++)
	{
		in >> name;
		in >> busCount;
		for (int j = 0; j < busCount; j++)
		{
			in >> busNumber;
			in >> scheduleCount;

			stops[name][busNumber].reserve(scheduleCount);
			for (int v = 0; v < scheduleCount; v++)
			{
				in >> currentMinutes;
				stops[name][busNumber].push_back(currentMinutes);
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

bool readFile(std::map<int, std::vector<std::string>>& busses, std::map<std::string, std::map<int, std::vector<int>>>& stops) {
	std::ifstream in(fileName);
	if (!in) {
		return false;
	}

	readStops(stops, in);
	readBusses(busses, in);

	return true;
}

void printStops(std::map<std::string, std::map<int, std::vector<int>>>& stops) {
	std::cout << "All stops are: ";
	for (const std::pair<std::string, std::map<int, std::vector<int>>>& stop:stops)
	{
		std::cout << stop.first << " ";
	}
}

void makeGraph(Graph& graph, std::map<std::string, std::map<int, std::vector<int>>>& stops, std::map<int, std::vector<std::string>>& busses) {
	for (const std::pair<int, std::vector<std::string>>& bus:busses)
	{
		for (int i = 1; i < bus.second.size(); i++)
		{
			std::string firstStop = bus.second[i - 1];
			std::string secondStop = bus.second[i];
			int timeToTravel = stops[secondStop][bus.first][0] - stops[firstStop][bus.first][0];
			graph.addEdge(firstStop, secondStop, timeToTravel);
		}
	}
}

int main() {
	std::map<int,std::vector<std::string>> busses;
	std::map<std::string, std::map<int,std::vector<int>>> stops;
	//std::vector<Stop*> stops;

	if (!readFile(busses, stops)) {
		std::cout << "No file with name " << fileName;
		return 0;
	}

	printStops(stops);

	Graph graph;
	makeGraph(graph,stops,busses);
	std::cout << "test\n";

	return 0;
}