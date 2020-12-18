#include <iostream>
#include <vector>
struct Node
{
	int data;
	std::vector<Node*> fChildren;
	Node(int data = 0) :data(data) {};
};

Node* createTree() {
	int count = 0;
	Node* root = new Node(count++);
	root->fChildren.push_back(new Node(count++));
	root->fChildren.push_back(new Node(count++));
	root->fChildren.push_back(new Node(count++));

	root->fChildren[0]->fChildren.push_back(new Node(count++));

	root->fChildren[1]->fChildren.push_back(new Node(count++));
	root->fChildren[1]->fChildren.push_back(new Node(count++));

	root->fChildren[2]->fChildren.push_back(new Node(count++));

	root->fChildren[2]->fChildren[0]->fChildren.push_back(new Node(count++));
	root->fChildren[2]->fChildren[0]->fChildren.push_back(new Node(count++));
	root->fChildren[2]->fChildren[0]->fChildren.push_back(new Node(count++));
	root->fChildren[2]->fChildren[0]->fChildren.push_back(new Node(count++));
	root->fChildren[2]->fChildren[0]->fChildren.push_back(new Node(count++));

	return root;
}

Node* createNiceTree()
{
	Node* root = new Node;
	root->data = 10;
	root->fChildren.push_back(new Node(4));
	root->fChildren.push_back(new Node(3));
	root->fChildren.push_back(new Node(3));

	root->fChildren[0]->fChildren.push_back(new Node(3));
	root->fChildren[0]->fChildren.push_back(new Node(1));

	root->fChildren[1]->fChildren.push_back(new Node(2));
	root->fChildren[1]->fChildren.push_back(new Node(1));

	root->fChildren[0]->fChildren[0]->fChildren.push_back(new Node(1));
	root->fChildren[0]->fChildren[0]->fChildren.push_back(new Node(1));
	root->fChildren[0]->fChildren[0]->fChildren.push_back(new Node(1));

	return root;
}

void deleteTree(Node* root) {
	for (Node* child : root->fChildren)
		deleteTree(child);

	delete root;
}

int findHeight(const Node* root) {
	int maxHeight = 0;

	for (const Node* child : root->fChildren) {
		int currentHeight = findHeight(child);

		if (currentHeight > maxHeight) {
			maxHeight = currentHeight;
		}
	}

	return 1 + maxHeight;
}

int findWidth(const Node* root) {
	int maxWidth = root->fChildren.size();

	for (const Node* child : root->fChildren) {
		int currentWidth = findWidth(child);

		if (currentWidth > maxWidth) {
			maxWidth = currentWidth;
		}
		
	}

	return maxWidth;
}

void printElementsOnLevel(int n,const Node* root) {
	if (n == 0) {
		std::cout << root->data << " ";
	}
	else {
		for (const Node* child : root->fChildren)
		{
			printElementsOnLevel(n - 1, child);
		}
	}
	
}

int findLeavesCount(const Node* root) {
	if (root->fChildren.empty()) {
		return 1;
	}
	int count = 0;
	for (const Node* child : root->fChildren)
	{
		count += findLeavesCount(child);
	}
	return count;
}

bool NodeEqualOfChildrenSum(const Node* root) {
	if (root->fChildren.empty()) {
		return root->data;
	}

	int sum = 0;
	for (const Node* child : root->fChildren)
	{
		sum += child->data;
	}

	if (sum != root->data) {
		return false;
	}

	for (const Node* child : root->fChildren)
	{
		if (!NodeEqualOfChildrenSum(child)) {
			return false;
		}
	}

	return true;
}

bool isPathCountN(const Node* root, int n) {
	if (root->fChildren.empty() && n - root->data == 0) {
		return true;
	}

	for (const Node* child : root->fChildren)
	{
		if (isPathCountN(child,n-root->data)) {
			return true;
		}
	}

	return false;
}

int main() {
	Node* root = createNiceTree();

	std::cout << "tree heigth: " << findHeight(root) <<" \n";

	std::cout << "tree width: " << findWidth(root) << " \n";

	printElementsOnLevel(2,root);

	std::cout << "\nlieves count:" << findLeavesCount(root) << "\n";

	if (NodeEqualOfChildrenSum(root)) {
		std::cout << "Is true\n";
	}
	else {
		std::cout << "Is false\n";
	}

	if (isPathCountN(root,33)) {
		std::cout << "Is true\n";
	}
	else {
		std::cout << "Is false\n";
	}

	deleteTree(root);

	return 0;
}