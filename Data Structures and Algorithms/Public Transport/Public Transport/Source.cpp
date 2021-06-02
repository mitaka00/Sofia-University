#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include<queue>
#include <set>

# define INF 0x3f3f3f3f
const char* fileName = "input.txt";

using string = std::string;
///Stored info about lines of every bus
using BusMap = std::unordered_map<int,std::vector<string>>; 
///Minutes of arrival of each bus at a stop
using ScheduleMap = std::unordered_map<int, std::vector<int>>; 
///Stored info about schedule of each stop
using StopsMap = std::unordered_map<std::string, ScheduleMap>; 

using Edge = std::pair < std::string, std::pair<int,int> >;
using Vertex = std::list< Edge >;
/// This struct represents a directed graph using 
/// adjacency list representation 
struct Graph
{
	/// In a weighted graph, we need to store vertex 
	/// and weight pair for every edge 
	std::unordered_map<string,Vertex > adj;
	
public:
	void addEdge(const string& firstStop, const string& secondStop, int weight, int busNumber);
};

///Add edge to Graph
void Graph::addEdge(const string& firstStop, const string& secondStop, int weight,int busNumber)
{
	adj[firstStop].push_back(std::make_pair(secondStop, std::make_pair(busNumber, weight)));
}

///Create stop in graph for every stop in StopsMap
void makeGraph(Graph& graph, StopsMap& stops) {
	for (const std::pair<string, ScheduleMap>& stop : stops) {
		graph.adj[stop.first];
	}
}

///Add edges in graph for every bus line
void addEdgesToGraph(Graph& graph, StopsMap& stops, BusMap& busses) {
	for (const std::pair<int, std::vector<string>>& bus : busses)
	{
		for (int i = 1; i < bus.second.size(); i++)
		{
			string firstStop = bus.second[i - 1];
			string secondStop = bus.second[i];
			int timeToTravel = stops[secondStop][bus.first][0] - stops[firstStop][bus.first][0];
			graph.addEdge(firstStop, secondStop, timeToTravel,bus.first);
		}
	}
}

///Fill distance and parents containers with default values
void fillDistanceAndParentContainers(std::unordered_map<string, int>& dist, std::unordered_map<string,string>& parent, const Graph& graph) {
	for (const std::pair<string,Vertex>& stop: graph.adj)
	{
		dist[stop.first] = INF;
		parent[stop.first] = "";
	}
}

///Calculate when will come the bus
int findMinutesOfStarting(int currentMinutes,const string& currentStop, int busNumber, StopsMap& stops) {
	for (const int minutes:stops[currentStop][busNumber])
	{
		if (minutes >= currentMinutes) {
			return minutes;
		}
	}

	return 0;
}

///Print the final result for shortest path (use it only in "shortestPath" function)
void printResult(const string& from,const string& to, int startedMinutes, std::unordered_map<string, string>& parent, std::unordered_map<string, int>& dist) {
	///Print the shortest time to reach the final destination
	std::cout << "The fastest way to move from " << from << " to " << to << " will take you " << dist[to] - startedMinutes << " minutes. " <<
		"You will arrive at "<<dist[to]<<" minutes\n";

	///Print the path

	///Add path in stack
	std::stack<string> path;
	string currentStop=to;
	path.push(to);
	do {
		currentStop = parent[currentStop];
		path.push(currentStop);
	} while (currentStop != "");
	path.pop(); ///Pop the white space in stack

	///Print the elements in the stack
	std::cout << "This is the shortest path:\n";
	while (!path.empty()) {
		if (path.top() == to) {
			std::cout << path.top() << std::endl;
		}
		else {
			std::cout << path.top() << " -> ";
		}
		path.pop();
	}
}



///Dejkstra algorithm
//TODO... change set to priority queue
void shortestPath(const string& src,const string& finalDistanation, int minutes, const Graph& graph, StopsMap& stops)
{
	int startedMinutes = minutes;
	if (graph.adj.find(src) == graph.adj.end() || graph.adj.find(finalDistanation) == graph.adj.end()) {
		std::cout << "No path from " << src << " to " << finalDistanation << std::endl;
		return;
	}
	/// Create a set to store vertices that are being processed 
	std::set< string > setds;

	/// Create a map for distances
	std::unordered_map<string, int> dist;

	/// Create a map for parent that will help you to find the correct path
	std::unordered_map<string, string> parent;

	/// Fill distances as infinite (INF) and parents as empty string
	fillDistanceAndParentContainers(dist, parent ,graph);
	

	/// Insert source itself in Set and initialize its 
	/// Distance as current minutes. 
	setds.insert(src);
	dist[src] = minutes;

	/** Looping till all shortest distance are finalized
	 *	then setds will become empty 
	 */
	while (!setds.empty())
	{
		/// The first vertex in Set is the minimum distance 
		/// vertex, extract it from set. 
		string from = *(setds.begin());
		setds.erase(setds.begin());

		minutes = dist[from];
		/// Vertex label is stored in second of pair (it 
		/// has to be done this way to keep the vertices 
		/// sorted distance (distance must be first item 
		/// in pair) 

		for (const Edge& el : (*graph.adj.find(from)).second)
		{
			/// Get vertex label and weight of current adjacent 
			/// of "from". 
			string to = el.first;
			int weight = el.second.second;
			int busNumber = el.second.first;

			///Minutes when bus start from this stop
			int startingMinutes = findMinutesOfStarting(minutes, from, busNumber, stops);
			int currentMinutes = INF;
			if (startingMinutes != 0) {
				currentMinutes = startingMinutes + weight;
			}

			/// If there is shorter path to "to" through "from". 
			if (dist[to] > currentMinutes)
			{
				/** If distance of "to" is not INF then it must be in
				*our set, so removing it and inserting again
				*with updated less distance.
				 */
				if (dist[to] != INF)
					setds.erase(to);

				/// Updating distance of "to" 
				parent[to] = from;
				dist[to] = currentMinutes;
				setds.insert(to);
			}
		}
	}
	
	///Print the final result after Dejkstra algorithm
	if (dist[finalDistanation] == INF) {
		std::cout << "No line from " << src << " to " << finalDistanation << std::endl;
	}
	else {
		printResult(src, finalDistanation, startedMinutes, parent, dist);
	}
}

///Read stops information from file
void readStops(StopsMap& stops, std::ifstream& in) {
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

///Read busses information from file
void readBusses(BusMap& busses, std::ifstream& in) {
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

///Read inputFile
bool readFile(BusMap& busses, StopsMap& stops) {
	std::ifstream in(fileName);
	if (!in) {
		return false;
	}

	readStops(stops, in);
	readBusses(busses, in);

	return true;
}

///Print all stops information
void printStops(const StopsMap& stops) {
	std::cout << "All stops are: ";
	for (const std::pair<string, ScheduleMap>& stop:stops)
	{
		std::cout << stop.first << " ";
	}
	std::cout << std::endl;
}

///Print all busses information
void printBusses(const BusMap& busses) {
	std::cout << "All busses are: ";
	for (const std::pair<int, std::vector<string>>& bus : busses)
	{
		std::cout << bus.first << " ";
	}
	std::cout << std::endl;
}

///Read information from console (helper function to shortestPath function)
void writeInfoForSearching(string& from, string& to, int& minutes) {
	std::cout << "Input starting stop: ";
	std::cin >> from;

	std::cout << "Input starting minutes: ";
	std::cin >> minutes;

	std::cout << "Input final stop: ";
	std::cin >> to;
}

///Print all commands on console
void printHelp() {
	std::cout << " - List of commands - " << std::endl
		<< "\tallStops - print all created stops." << std::endl
		<< "\tallBusses - print all created busses." << std::endl
		<< "\tbusInfo <number> - shows info about the bus with that number." << std::endl
		<< "\tstopInfo <name> - shows info about the stop with that name." << std::endl
		<< "\tfindPath - find the shortest path between two stops." << std::endl
		<< "\taddStop <name> - add new stop with that name." << std::endl
		<< "\tdeleteStop <name> - delete stop with that name." << std::endl
		<< "\taddLine <busNumber> - add new bus with that number and make new line." << std::endl
		<< "\tdeleteLine <busNumber> - delete bus with that number and delete the line." << std::endl
		<< "\taddCourse <busNumber> - add new course at the end of any of the lines." << std::endl
		<< "\tdeleteCourse <busNumber> - delete the last course at the end of \"busNumber\" line." << std::endl
		<< "\thelp - shows info about the commands." << std::endl
		<< "\tfinish - terminates the program." << std::endl;
}

///Print info about bus with number=busNumber
void printBusInfo(int busNumber,BusMap& busses) {
	///busNumber validation
	if (busses.find(busNumber) == busses.end()) {
		std::cout << "No bus with this number\n";
		return;
	}

	///Print on console
	std::cout << "The path for bus with number " << busNumber << " is:";
	for (const string& stop : busses[busNumber]) {
		std::cout << stop << " ";
	}

	std::cout << std::endl;
}

///Print info about stop with name=stopName
void printStopInfo(const string& stopName,StopsMap& stops) {
	///stopName validation
	if (stops.find(stopName) == stops.end()) {
		std::cout << "No stop with this name\n";
		return;
	}

	///Print on console
	std::cout << "The info for the stop with name " << stopName << " is:\n";
	for (const std::pair<int,std::vector<int>>& busInfo : stops[stopName]) {
		std::cout << "Bus with number " << busInfo.first << " will come to this stop at:";
		for (const int& minute : busInfo.second) {
			std::cout << minute << " ";
		}
		std::cout << std::endl;
	}
}

///Add stop with name=stopName
void addStop(const string& stopName, StopsMap& stops,Graph& graph) {
	///stopName validation
	if (stops.find(stopName) != stops.end()) {
		std::cout << "Already have stop with that name\n";
		return;
	}

	///Add stop to graph and stopsMap
	stops[stopName];
	graph.adj[stopName];
	std::cout << "The stop is added successfully\n";
}

///Delete stop with name=stopName
void deleteStop(const string& stopName, StopsMap& stops, Graph& graph) {
	///stopName validation
	if (stops.find(stopName) == stops.end()) {
		std::cout << "Invalid stop name\n";
		return;
	}

	///Delete stop
	
	///1.Check for permission to delete stop
	if (!stops[stopName].empty()) {
		std::cout << "This stop is included in a line. You can't delete the stop.\n";
		return;
	}

	///2.Delete stop from stops and graph
	stops.erase(stopName);
	graph.adj.erase(stopName);
	std::cout << "The stop is deleted successfully\n";
}

///Add new line in Graph
void addNewLine(int& busNumber, BusMap& busses, StopsMap& stops, Graph& graph) {
	///busNumber validation
	if (busses.find(busNumber) != busses.end()) {
		std::cout << "Already have bus with this number\n";
		return;
	}

	///Input from console the stops that this line will include

	///Input count of stops
	int stopsCount;
	std::cout << "Write count of stops in this line:";
	std::cin >> stopsCount;
	if (stopsCount <= 1) {
		std::cout << "Count must be > 1\n";
		return;
	}
	busses[busNumber].reserve(stopsCount);

	///Input name of stops (You can add only existing stops)
	std::cout << "Write stops in this line:\n";
	for (int i = 1; i <= stopsCount; i++)
	{
		bool isCorrect = true;
		string stopName;
		std::cout << "Stop number " << i << ":";
		std::cin >> stopName;

		///Check is correct stop
		if (stops.find(stopName) == stops.end()) {
			std::cout << "Invalid stop name\n";
			i--;
			isCorrect = false;
		}
		
		///Check is already added in the line
		for (const string& stop:busses[busNumber])
		{
			if (stop == stopName) {
				std::cout << "This stop is already added in this line.\n";
				i--;
				isCorrect = false;
				break;
			}
		}

		///Add stop to the line
		if (isCorrect) {
			busses[busNumber].push_back(stopName);
			std::cout << std::endl;
		}
	}

	///Add the starting minutes of the line
	int startingMinutes, coursesCount;
	std::cout << "How much courses will make this line:";
	std::cin >> coursesCount;

	for (int i = 1; i <= coursesCount; i++)
	{
		std::cout << "Write the starting minutes of course " << i << ":";
		std::cin >> startingMinutes;

		stops[busses[busNumber][0]][busNumber].push_back(startingMinutes);
	}

	///Add minutes that will take you to travel between every stop
	int minutes;
	for (int i = 1; i < busses[busNumber].size(); i++)
	{
		string to = busses[busNumber][i];
		string from = busses[busNumber][i - 1];
		std::cout << "Write minutes that will take you to reach " << to << " from " << from << std::endl;
		std::cin >> minutes;

		//Add edge in Graph
		graph.addEdge(from, to, minutes, busNumber);
		for (int j = 0; j < stops[from][busNumber].size(); j++)
		{
			stops[to][busNumber].push_back(stops[from][busNumber][j]+minutes);
		}
	}

	std::cout << "The line is added successfully\n";
}

///Delete line from Graph
void deleteLine(int& busNumber, BusMap& busses, StopsMap& stops, Graph& graph) {
	///busNumber validation
	if (busses.find(busNumber) == busses.end()) {
		std::cout << "Invalid bus number\n";
		return;
	}

	///Delete info about every stop in this line
	for (const string& stop : busses[busNumber]) {
		//Delete from StopsMap
		stops[stop].erase(busNumber);

		///Delete from Graph
		std::list<Edge>::iterator i = (*graph.adj.find(stop)).second.begin();
		while (i != (*graph.adj.find(stop)).second.end())
		{
			if ((*i).second.first==busNumber)
			{
				graph.adj[stop].erase(i++);
				break;
			}
			++i;
		}
	}

	///Delete from BusMap
	busses.erase(busNumber);

	std::cout << "The line is deleted successfully\n";
}

///Add new course to line
void addNewCourse(int& busNumber ,BusMap& busses,StopsMap& stops , Graph& graph) {
	///Course validation
	if (busses.find(busNumber) == busses.end()) {
		std::cout << "No bus with that number\n";
		return;
	}

	bool isCorrectName = false;
	string newStopName;

	///Write the name of the new stop
	while (!isCorrectName) {
		isCorrectName = true;
		std::cout << "Write the new stop for bus with number " << busNumber << ":";
		std::cin >> newStopName;

		if (stops.find(newStopName) == stops.end()) {
			isCorrectName = false;
			std::cout << "Invalid stop name\n";
			continue;
		}

		for (const string& stop : busses[busNumber]) {
			if (stop == newStopName) {
				isCorrectName = false;
				std::cout << "This line already include this stop. Please try again.\n";
				break;
			}
		}
	}

	///Write the time that will take you to reach the new stop from the last
	int minutes;
	string lastStopName = busses[busNumber][busses[busNumber].size() - 1];
	std::cout << "How many minutes will take you to reach " << newStopName << " from " << lastStopName <<":";
	std::cin >> minutes;

	///Add edge in Graph
	graph.addEdge(lastStopName, newStopName, minutes, busNumber);

	///Update schedule for new line
	for (const int minute: stops[lastStopName][busNumber])
	{
		stops[newStopName][busNumber].push_back(minute + minutes);
	}

	//add to BusMap
	busses[busNumber].push_back(newStopName);

	std::cout << "New course is added successfully\n";
}

///Delete the last course of the line
void deleteCourse(int& busNumber, BusMap& busses, StopsMap& stops, Graph& graph) {
	///Course validation
	if (busses.find(busNumber) == busses.end()) {
		std::cout << "No bus with that number\n";
		return;
	}

	if (busses[busNumber].size() == 0) {
		std::cout << "There is no stop in this line.\n";
		return;
	}

	///Get the name of the last stop in the line
	string lastStop = busses[busNumber][busses[busNumber].size() - 1];

	///Delete last stop from the line
	busses[busNumber].pop_back();

	///Delete last stop schedule for this line
	stops[lastStop].erase(busNumber);

	///Delete edge from Graph if this is not the last stop from the line
	if (busses[busNumber].size() != 0) {
		string updatedLastStop = busses[busNumber][busses[busNumber].size() - 1];;
		std::list<Edge>::iterator i = (*graph.adj.find(updatedLastStop)).second.begin(); //get updated last stop iterator
		while (i != (*graph.adj.find(updatedLastStop)).second.end())
		{
			if ((*i).second.first == busNumber)
			{
				graph.adj[updatedLastStop].erase(i++);
				break;
			}
			++i;
		}
	}
	
	std::cout << "The stop " << lastStop << " is removed from the line of bus with number " << busNumber << std::endl;

	///Check the length of the line.
	///If the length is only one stop, you must delete it.
	if (busses[busNumber].size() == 1) {
		deleteCourse(busNumber, busses, stops, graph);
	}
}

int main() {
	BusMap busses;
	StopsMap stops;

	///Read input file
	if (!readFile(busses, stops)) {
		std::cout << "No file with name " << fileName;
		return 0;
	}

	///Print info from file
	printStops(stops);
	printBusses(busses);

	///Create graph
	Graph graph;
	makeGraph(graph, stops);
	addEdgesToGraph(graph,stops,busses);

	printHelp();

	bool end = false;
	string input;

	///Read commands from console
	while (!end) {
		std::cout << "write command:\n";
		std::cin >> input;

		if (input == "findPath") {
			string from, to;
			int startingMinutes = 0;
			writeInfoForSearching(from, to, startingMinutes);
			shortestPath(from, to, startingMinutes, graph, stops);
		}
		else if (input == "allStops") {
			printStops(stops);
		}
		else if (input == "allBusses") {
			printBusses(busses);
		}
		else if (input=="busInfo") {
			int busNumber;
			std::cin >> busNumber;
			printBusInfo(busNumber, busses);
		}
		else if (input=="stopInfo") {
			string stopName;
			std::cin >>stopName;
			printStopInfo(stopName, stops);
		}
		else if (input=="addStop") {
			string stopName;
			std::cin >> stopName;
			addStop(stopName,stops,graph);
		}
		else if (input == "deleteStop") {
			string stopName;
			std::cin >> stopName;
			deleteStop(stopName, stops, graph);
		}
		else if (input == "addLine") {
			int busNumber;
			std::cin >> busNumber;
			addNewLine(busNumber, busses, stops, graph);
		}
		else if (input == "deleteLine") {
			int busNumber;
			std::cin >> busNumber;
			deleteLine(busNumber, busses, stops, graph);
		}
		else if (input == "addCourse") {
			int busNumber;
			std::cin >> busNumber;
			addNewCourse(busNumber, busses, stops, graph);
		}
		else if (input == "deleteCourse") {
			int busNumber;
			std::cin >> busNumber;
			deleteCourse(busNumber, busses, stops, graph);
		}
		else if (input == "help") {
			printHelp();
		}
		else if (input == "finish") {
			end = true;
		}
		else {
			std::cout << "Unknown command! Type 'help' for available commands." << std::endl;
		}
	}

	return 0;
}