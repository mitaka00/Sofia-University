#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

const char* fileName = "input.txt";
const int MAX	= std::numeric_limits<int>::max();

int findIndex(const char& symbol,std::vector<char>& symbols) {
	for (int i = 0; i < symbols.size(); i++)
	{
		if (symbol == symbols[i]) {
			return i;
		}
	}

	return -1;
}

void fillGraph(std::vector<std::vector<int>>& colorsGraph, const int& graphSize) {
	colorsGraph.resize(2 * graphSize);
	for (int i = 0; i < 2 * graphSize; i++)
	{
		colorsGraph[i].resize(2 * graphSize);
		for (int j = 0; j < 2*graphSize; j++)
		{
			colorsGraph[i][j] = MAX;
		}
	}
}

bool readFile(std::vector<std::vector<int>>& colorsGraph, std::vector<char>& symbols, std::string& firstWord, std::string& secondWord) {
	std::ifstream in(fileName);

	if (!in) {
		return false;
	}
	else {
		int wordsLength, graphSize;

		in >> wordsLength;
		in >> graphSize;

		fillGraph(colorsGraph,graphSize);

		in.ignore();
		in >> firstWord;
		in >> secondWord;

		for (int i = 0; i < graphSize; i++)
		{
			char firstChar, secondChar;
			int num;

			in >> firstChar >> secondChar >> num;

			int firstCharIndex = findIndex(firstChar, symbols);
			if (firstCharIndex == -1) {
				symbols.push_back(firstChar);
				firstCharIndex = symbols.size() - 1;
			}

			int secondCharIndex = findIndex(secondChar, symbols);
			if (secondCharIndex == -1) {
				symbols.push_back(secondChar);
				secondCharIndex = symbols.size() - 1;
			}

			colorsGraph[firstCharIndex][secondCharIndex] = num;
		}
	}

	in.close();
	return true;
}

int min(const int& x, const int& y) {
	return ((x) < (y)) ? (x) : (y);
}

//Floyd Warshall algorithm
//Code from exercises
void findShortestPaths(std::vector<std::vector<int>>& graph) {
	int size = graph.size();
	for (size_t k = 0; k < size; k++)           // for each vertex
		for (size_t i = 0; i < size; i++)       // between i
			for (size_t j = 0; j < size; j++) { // and j
												// don't optimize path from vertex to itself
				if (i == j) continue;
				// if there is no edge from i to k or from k to j skip this step
				if (graph[i][k] == MAX || graph[k][j] == MAX) continue;
				// remember the old value, debug purpose only
				int old = graph[i][j];
				// try to optimize the path
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
				/* debug only
				if (old != graph[i][j]) {
					printf("optimizing path from %c to %c through %c (%d->%d)\n",
						'A' + i, 'A' + j, 'A' + k, old, graph[i][j]);
				}
				*/
			}
}

char findLetter(std::vector<std::vector<int>>& graph, std::vector<char>& symbols, const char& firstLetter, const char& secondLetter, int& sum) {
	char resultLetter=' ';
	int finalPrice = MAX;
	int firstLetterValue, secondLetterValue;
	int firstLetterIndex = findIndex(firstLetter, symbols);
	int secondLetterIndex = findIndex(secondLetter, symbols);

	if (firstLetterIndex == -1 || secondLetterIndex == -1) {
		sum = -1;
		return resultLetter;
	}

	for (int i = 0; i < graph.size(); i++)
	{
		int currentPrice;
		if (firstLetterIndex == i) {
			firstLetterValue = 0;
		}
		else {
			firstLetterValue = graph[firstLetterIndex][i];
		}

		if (secondLetterIndex == i) {
			secondLetterValue = 0;
		}
		else {
			secondLetterValue = graph[secondLetterIndex][i];
		}
		
		
		if (firstLetterValue!=MAX && secondLetterValue!=MAX) {
			currentPrice = firstLetterValue + secondLetterValue;
			if (currentPrice < finalPrice) {
				finalPrice = currentPrice;
				resultLetter = symbols[i];
			}
		}
	}

	if (finalPrice == MAX) {
		sum = -1;
	}
	else {
		sum += finalPrice;
	}
	return resultLetter;
}

int main() {
	std::vector<std::vector<int>> colorsGraph;
	std::vector<char> symbols;
	std::string firstWord, secondWord,result;
	int sum = 0;

	if (readFile(colorsGraph,symbols, firstWord, secondWord)) {
		findShortestPaths(colorsGraph);
		int size = firstWord.size();
		for (size_t i = 0; i < size; i++)
		{
			if (firstWord[i] != secondWord[i]) {
				result += findLetter(colorsGraph, symbols, firstWord[i], secondWord[i], sum);
				if (sum == -1) {
					result = "Not possible\n";
					break;
				}
			}
			else {
				result += firstWord[i];
			}
		}

		std::cout << sum << std::endl;
		std::cout << result;

	}
	else {
		std::cout << "No " << fileName << " file\n";
	}

	return 0;
}