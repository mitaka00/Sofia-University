//Не е завършено нацяло

#pragma once
#include <iostream>
const int MAX_LENGTH = 5;
const int MAX_NAME_LENGTH = 31;

class Matrix
{
public:
	Matrix(const char* name = "", int row = 0,int col=0);
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();

	friend std::ostream& operator<<(std::ostream& out,const Matrix& obj);
	friend std::istream& operator>>(std::istream& in, Matrix& obj);
	
	int calcDeterm() const;

	Matrix& operator+=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator*=(const int number);

	Matrix operator+(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Matrix operator*(const int number) const;

	Matrix operator~();

	const char* getName() const;
	Matrix& setName(const char* name);
	int getIndex(int row, int col) const;
	Matrix& setIndex(const int row,const int col,const int result);

private:
	char* name;
	int matrix[MAX_LENGTH][MAX_LENGTH];
	int row;
	int col;

	void setSize(int row, int col);
	void copy(const Matrix& other);
	void clear();
	void fillMatrix();
	void changeName(const char* symbol,const Matrix& other);
};

