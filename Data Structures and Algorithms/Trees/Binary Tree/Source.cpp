#include <iostream>
#include <functional> 

struct Node {
	Node* lPtr;
	Node* rPtr;
	int data;
	Node(int data = 0) :data(data), lPtr(nullptr), rPtr(nullptr) {};
};

Node* initTree() {
	Node* root = new Node(5);

	root->lPtr = new Node(4);
	root->rPtr = new Node(11);

	root->lPtr->lPtr = new Node(3);
	root->rPtr->lPtr = new Node(10);
	root->rPtr->rPtr = new Node(13);

	root->lPtr->lPtr->lPtr = new Node(1);
	root->rPtr->rPtr->lPtr = new Node(9);

	return root;
}

void deleteTree(Node*& root) {
	if (root) {
		deleteTree(root->lPtr);
		deleteTree(root->rPtr);

		delete root;
		root = nullptr;
	}
}

bool isLeaf(const Node* node) {
	return (node && !node->lPtr && !node->rPtr);
}

void printLeftCenterRight(const Node* root) {
	if (root) {
		printLeftCenterRight(root->lPtr);
		std::cout << root->data << " ";
		printLeftCenterRight(root->rPtr);
	}
}

bool isValidBinaryTree(const Node* root) {
	if (!root) {
		return true;
	}

	if (root->lPtr && root->data < root->lPtr->data) {
		return false;
	}

	if (root->rPtr && root->data > root->rPtr->data) {
		return false;
	}

	return isValidBinaryTree(root->lPtr) && isValidBinaryTree(root->rPtr);
}

void mapFunction(int& data) {
	data += 100;
}

void treeMap(Node* root, const std::function<void(int&)>& f) {
	if (root) {
		treeMap(root->lPtr,f);
		f(root->data);
		treeMap(root->rPtr,f);
	}
}

void trimTree(Node*& root) {
	if (isLeaf(root))
	{
		delete root;
		root = nullptr;
	}
	else
	{
		if (root->lPtr)
		{
			trimTree(root->lPtr);
		}
		if (root->rPtr)
		{
			trimTree(root->rPtr);
		}
	}
}

void bloomTree(Node*& root) {
	if (isLeaf(root)) {
		root->lPtr = new Node(root->data);
		root->rPtr = new Node(root->data);
	}
	else {
		if (root->lPtr)
		{
			bloomTree(root->lPtr);
		}
		if (root->rPtr)
		{
			bloomTree(root->rPtr);
		}
	}
}

int main() {
	Node* root = initTree();
	printLeftCenterRight(root);
	
	if (isValidBinaryTree(root)) {
		std::cout << "Is valid\n";
	}
	else {
		std::cout << "Is NOT valid\n";
	}

	treeMap(root, mapFunction);
	printLeftCenterRight(root);

	std::cout << std::endl;

	trimTree(root);
	printLeftCenterRight(root);

	std::cout << std::endl;

	bloomTree(root);
	printLeftCenterRight(root);

	deleteTree(root);

	return 0;
}