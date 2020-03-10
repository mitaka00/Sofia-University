#include "Vector.h"
#include <iostream>

Vector::Vector()
{
	capacity = 4;
	size = 0;

	array = new  int[capacity];
}

Vector::Vector(const Vector& other)
{
	copy(other);
}

Vector::~Vector()
{
	deleteArr();
}

Vector& Vector::operator=(const Vector& other)
{
	if (this != &other) {
		deleteArr();
		copy(other);
	}

	return *this;
}

int Vector::getCapacity()
{
	return capacity;
}

int Vector::getSize()
{
	return size;
}

void Vector::push_back(int num)
{
	if (capacity > size+1) {
		array[size] = num;
		size++;
	}
	else {
		reserve(1);
		array[size] = num;
		size++;
	}
}

int Vector::at(int index)
{
	return array[index];
}

void Vector::reserve(int size)
{
	capacity += size;

	int* secondArr = new int[capacity];
	for (int i = 0; i < size; i++)
	{
		secondArr[i] = array[i];
	}

	delete[] array;
	array = secondArr;
}

void Vector::erase(int index)
{
	for (int i = index; i < size - 1; i++)
	{
		array[i] = array[i + 1];
	}
	size--;
}

void Vector::deleteArr()
{
	delete[] array;
	size = 0;
	capacity = 4;
}
void Vector::copy(const Vector& other)
{
	capacity = other.capacity;
	size = other.size;
	array = new  int[capacity];
	for (int i = 0; i < size; i++)
	{
		array[i] = other.array[i];
	}
}

