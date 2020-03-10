#pragma once
#include<iostream>
class Vector
{
public:
	Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();


	int getCapacity();
	int getSize();

	void push_back(int num);
	int at(int num);
	void reserve(int size);
	void erase(int index);

private:
	int* array;
	int capacity;
	int size;
	void deleteArr();
	void copy(const Vector& other);
};

