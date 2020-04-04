#pragma once
#include <iostream>
class RationalNumber
{
public:
	RationalNumber(int numerator = 0, int denominator=0);

	RationalNumber& operator+=(const RationalNumber& other);
	RationalNumber& operator-=(const RationalNumber& other);
	RationalNumber& operator*=(const RationalNumber& other);
	RationalNumber& operator/=(const RationalNumber& other);

	RationalNumber operator+(const RationalNumber& other) const;
	RationalNumber operator-(const RationalNumber& other) const;
	RationalNumber operator*(const RationalNumber& other) const;
	RationalNumber operator/(const RationalNumber& other) const;

	bool operator==(const RationalNumber& other) const;
	bool operator>=(const RationalNumber& other) const;
	bool operator<=(const RationalNumber& other) const;
	bool operator>(const RationalNumber& other) const;
	bool operator<(const RationalNumber& other) const;

	RationalNumber& operator++(); //prefix
	RationalNumber operator++(int); //postfix
	RationalNumber& operator--(); //prefix
	RationalNumber operator--(int); //postfix

	// Unary -
	RationalNumber operator-() const;
	// Reciprocal
	RationalNumber operator~() const;

	// Conversion operators
	operator double() const;
	explicit operator float() const;


	double getNumerator() const;
	double getDenominator() const;

	RationalNumber& setNumerator(int nominator);
	RationalNumber& setDenominator(int denominator);

	friend std::ostream& operator<<(std::ostream& out, const RationalNumber& obj);
	friend std::istream& operator>>(std::istream& in, RationalNumber& obj);

	void simplify();
private:
	int numerator;
	int denominator;
};

