#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <set>

using GraphAdjLists = std::vector<std::list<int>>;

bool hasEdge(const GraphAdjLists& graph, size_t from, size_t to) // O(|E|)
{
	for (size_t neighbour : graph[from])
		if (neighbour == to)
			return true;

	return false;
}

void addEdgeOriented(GraphAdjLists& graph, size_t from, size_t to) // O(|E|)
{
	if (!hasEdge(graph, from, to))
		graph[from].push_front(to);
}

void addEdgeUnoriented(GraphAdjLists& graph, size_t from, size_t to) // O(|E|)
{
	addEdgeOriented(graph, from, to);
	addEdgeOriented(graph, to, from);
}

void dfsRemoveElements(const GraphAdjLists& graph, size_t from, std::set<int>& nodes) {
	nodes.erase(from);

	for (int node : graph[from]) {
		if (nodes.find(node) != nodes.end())
			dfsRemoveElements(graph, node, nodes);
	}
}

int componentsCount(GraphAdjLists& graph, int nodesCount) {
	int componentsCount = 0;
	std::set<int> nodes;

	for (int i = 0; i < nodesCount; i++)
	{
		nodes.insert(i);
	}

	while (!nodes.empty()) {
		dfsRemoveElements(graph, *nodes.begin(), nodes);
		componentsCount++;
	}

	return componentsCount;
}

//BFS
int shortestPath(const GraphAdjLists& graph, size_t from, size_t to) {
	bool* visited = new bool[graph.size()];
	for (int i = 0; i < graph.size(); i++) {
		visited[i] = false;
	}
		
	std::queue<int> wave;
	wave.push(from);
	wave.push(-1); // delimiter

	visited[from] = true;
	int distance = 0;

	while (!wave.empty()) {
		int currentIndex = wave.front();
		wave.pop();

		if (currentIndex == to) {
			return distance;
		}

		if (currentIndex == -1)
		{
			if (wave.empty())
			{
				return -1;
			}
			wave.push(-1);
			distance++;
		}
		else
		{
			for (int element : graph[currentIndex]) {
				if (!visited[element])
				{
					visited[element] = true;
					wave.push(element);
				}
			}
		}
	}

	return distance;
}

int main() {
	GraphAdjLists graphUnoriented;

	graphUnoriented.resize(19);
	{
		addEdgeUnoriented(graphUnoriented, 0, 1);
		addEdgeUnoriented(graphUnoriented, 1, 2);
		addEdgeUnoriented(graphUnoriented, 1, 3);
		addEdgeUnoriented(graphUnoriented, 3, 4);
		addEdgeUnoriented(graphUnoriented, 3, 6);
		addEdgeUnoriented(graphUnoriented, 7, 3);
		addEdgeUnoriented(graphUnoriented, 3, 10);
		addEdgeUnoriented(graphUnoriented, 6, 5);
		addEdgeUnoriented(graphUnoriented, 6, 7);
		addEdgeUnoriented(graphUnoriented, 7, 8);
		addEdgeUnoriented(graphUnoriented, 10, 9);

		addEdgeUnoriented(graphUnoriented, 11, 12);
		addEdgeUnoriented(graphUnoriented, 12, 13);

		addEdgeUnoriented(graphUnoriented, 15, 16);
		addEdgeUnoriented(graphUnoriented, 15, 17);
		addEdgeUnoriented(graphUnoriented, 16, 18);
		addEdgeUnoriented(graphUnoriented, 17, 18);
	}

	std::cout << shortestPath(graphUnoriented, 0, 5) << std::endl;
	std::cout << componentsCount(graphUnoriented,19);


	return 0;
}