#include <iostream>

struct Node {
	Node* lPtr;
	Node* rPtr;
	int data;
	Node(int data = 0) :data(data), lPtr(nullptr), rPtr(nullptr) {};
};

int main() {
	return 0;
}