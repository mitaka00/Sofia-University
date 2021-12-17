#pragma once

#include <iostream>
#include "MyStore.h"
//Списъкът има имплементирана единствено логика нужна за задачата, без допълнителни методи.
//Умишлено е оставен достъпът до ноудовете за по-лесно използване на структурата в задачата.

template <typename T>
struct MyList {
	struct node {
		T data;
		node* next;
		node* prev;

		node(T data, node* prevNode = nullptr, node* nextNode = nullptr)
			: data(data), prev(prevNode), next(nextNode) {}
	};

	node* head, *tail;
	int size;
	MyList() :head(nullptr), tail(nullptr), size(0) {};
	~MyList() { clear(); };

	void push_back(T data);
	void remove(node* currentNode);

	bool empty() { return size == 0; };

private:
	void clear();
};


template<typename T>
void MyList<T>::push_back(T data) {
	if (size == 0) {
		head = new node(data);
		tail = head;
	}
	else {
		tail->next = new node(data, tail, nullptr);
		tail = tail->next;
	}
	size++;
}

template<typename T>
void MyList<T>::remove(node* currentNode) {
	if (size == 0) {
		throw std::exception("The list is empty");
	}
	else if (size == 1) {
		delete currentNode;
		tail = nullptr;
		head = nullptr;
	}
	else if (currentNode == head) {
		head = currentNode->next;
	}
	else if (currentNode == tail) {

	}
	else {
		node* token = currentNode;
		currentNode->prev->next = currentNode->next;
		currentNode->next->prev = currentNode->prev;
		delete currentNode;
	}
	size--;
}

template<typename T>
void MyList<T>::clear() {
	while (!empty()) {
		remove(head);
	}
}


