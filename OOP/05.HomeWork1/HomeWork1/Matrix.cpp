#include "Matrix.h"
#include <cstring>

Matrix::Matrix(const char* name, int row, int col)	
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	setSize(row, col);
	fillMatrix();
}

Matrix::Matrix(const Matrix& other)
{
	copy(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}

	return *this;
}

Matrix::~Matrix()
{
	clear();
}

int Matrix::calcDeterm() const 
{
	if (row == col && row <= 3) {
		if (row == 0) {
			return 0;
		}
		else if (row == 1) {
			return matrix[0][0];
		}
		else if (row == 2) {
			return (matrix[0][0] * matrix[1][1] - (matrix[0][1] * matrix[1][0]));
		}
		else {
			int firstNum = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[3][0] + matrix[0][3] * matrix[1][0] * matrix[2][1];
			int secondNum = matrix[0][2] * matrix[1][1] * matrix[2][0] + matrix[0][0] * matrix[1][2] * matrix[2][1] + matrix[0][1] * matrix[1][0] * matrix[2][2];
			return firstNum - secondNum;
		}
	}
	return -1;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (row == other.row && col == other.col) {
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				matrix[i][j] += other.matrix[i][j];
			}
		}

		changeName("+", other);
	}

	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	int sum = 0;
	if (row == other.col && col == other.row) {
		for (int c = 0; c < row; c++) {
			for (int d = 0; d < other.col; d++) {
				for (int k = 0; k < col; k++) {
					sum += matrix[c][k] * other.matrix[k][d];
				}

				matrix[c][d] = sum;
				sum = 0;
			}
		}

		changeName("*", other);
	}

	return *this;
}

Matrix& Matrix::operator*=(const int number)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] *= number;
		}
	}

	char num[32];
	itoa(number,num,10);
	char* token = new char[strlen(name) + strlen(num) + 1];
	strcpy(token, num);
	strcat(token, name);
	delete[] name;
	name = token;

	return *this;
}

Matrix Matrix::operator+(const Matrix& other) const
{
	return Matrix(*this)+=other;
}

Matrix Matrix::operator*(const Matrix& other) const
{
	return Matrix(*this)*=other;
}

Matrix Matrix::operator*(const int number) const
{
	return Matrix(*this)*=number;
}

Matrix Matrix::operator~()
{
	Matrix newObj(*this);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			newObj.matrix[j][i] = matrix[i][j];
		}
	}
	newObj.name = new char[strlen(name) + 2];
	strcpy(newObj.name, name);
	strcat(newObj.name, "t");

	return newObj;
}

const char* Matrix::getName() const
{
	return name;
}

Matrix& Matrix::setName(const char* name)
{
	clear();
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	return *this;
}

int Matrix::getIndex(int row, int col) const
{
	return matrix[row - 1][col - 1];
}

Matrix& Matrix::setIndex(const int row,const int col,const int result)
{
	if (row < this->row && col < this->col) {
		matrix[row][col] = result;
	}

	return *this;
}

void Matrix::setSize(int row, int col)
{
	if (row > MAX_LENGTH) {
		this->row = MAX_LENGTH;
	}
	else {
		this->row = row;
	}

	if (col > MAX_LENGTH) {
		this->col = MAX_LENGTH;
	}
	else {
		this->col = col;
	}
}

void Matrix::copy(const Matrix& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	setSize(other.row, other.col);
	for (int i = 0; i < other.row; i++)
	{
		for (int j = 0; j < other.col; j++)
		{
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

void Matrix::clear()
{
	delete[] name;
	name = nullptr;
}

void Matrix::fillMatrix()
{
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		for (int j = 0; j < MAX_LENGTH; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void Matrix::changeName(const char* symbol,const Matrix& other)
{
	char* token = new char[strlen(name) + 1 + strlen(other.name) + 1];
	strcpy(token, name);
	strcat(token, symbol);
	strcat(token, other.name);
	delete[] name;
	name = token;
}

std::ostream& operator<<(std::ostream& out,const Matrix& obj)
{
	out << obj.name << std::endl;
	for (int i = 0; i < obj.row; i++)
	{
		for (int j = 0; j < obj.col; j++) {
			out << obj.matrix[i][j] << " ";
		}
		out << std::endl;
	}

	return out;
}

std::istream& operator>>(std::istream& in, Matrix& obj)
{
	int token = 0;
	in.getline(obj.name, MAX_NAME_LENGTH);
	in >> obj.row;
	in >> obj.col;

	return in;
}


