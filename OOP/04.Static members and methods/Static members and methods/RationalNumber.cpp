#include "RationalNumber.h"
#include <iostream>
#include <numeric>
#include <cmath>

RationalNumber::RationalNumber(int numerator, int denominator)
	: numerator(numerator)
	, denominator(denominator)
{
	simplify();
}

RationalNumber& RationalNumber::operator+=(const RationalNumber& other)
{
	numerator = numerator * other.denominator + other.numerator * denominator;
	denominator *= other.denominator;
	simplify();

	return *this;
}

RationalNumber& RationalNumber::operator-=(const RationalNumber& other)
{
	return *this += -other;
}

RationalNumber& RationalNumber::operator*=(const RationalNumber& other)
{
	denominator *= other.denominator;
	numerator *= other.numerator;

	return *this;
}

RationalNumber& RationalNumber::operator/=(const RationalNumber& other)
{
	RationalNumber res = ~other;
	*this *= ~other;
	return *this;
}

RationalNumber RationalNumber::operator+(const RationalNumber& other) const
{
	return RationalNumber(*this)+=other;
}

RationalNumber RationalNumber::operator-(const RationalNumber& other) const
{
	return RationalNumber(*this) -= other;
}

RationalNumber RationalNumber::operator*(const RationalNumber& other) const
{
	return RationalNumber(*this) *= other;
}

RationalNumber RationalNumber::operator/(const RationalNumber& other) const
{
	return RationalNumber(*this) /= other;
}

bool RationalNumber::operator==(const RationalNumber& other) const
{
	return numerator/denominator==other.numerator/other.denominator;
}

bool RationalNumber::operator>=(const RationalNumber& other) const
{
	return !(*this < other);
}

bool RationalNumber::operator<=(const RationalNumber& other) const
{
	return (*this > other);
}

bool RationalNumber::operator>(const RationalNumber& other) const
{
	if (denominator* other.denominator < 0) {
		return numerator* other.denominator < denominator* other.numerator;
	}
	else {
		return numerator* other.denominator > denominator * other.numerator;
	}
}

bool RationalNumber::operator<(const RationalNumber& other) const
{
	if (denominator* other.denominator < 0) {
		return numerator* other.denominator > denominator* other.numerator;
	}
	else {
		return numerator* other.denominator < denominator * other.numerator;
	}
}

RationalNumber& RationalNumber::operator++()
{
	numerator += denominator;
	return *this;
}

RationalNumber RationalNumber::operator++(int)
{
	RationalNumber res(*this);
	++*this;
	return res;
}

RationalNumber& RationalNumber::operator--()
{
	numerator -= denominator;
	return *this;
}

RationalNumber RationalNumber::operator--(int)
{
	RationalNumber res(*this);
	--* this;
	return res;
}

RationalNumber RationalNumber::operator-() const
{
	return RationalNumber(-numerator, denominator);
}

RationalNumber RationalNumber::operator~() const
{
	return RationalNumber(denominator, numerator);
}

RationalNumber::operator double() const
{
	return numerator / (double)denominator;
}

RationalNumber::operator float() const
{
	return numerator / (float)denominator;
}

double RationalNumber::getNumerator() const
{
	return numerator;
}

double RationalNumber::getDenominator() const
{
	return denominator;
}

RationalNumber& RationalNumber::setNumerator(int numerator)
{
	this->numerator = numerator;
	simplify();
	return *this;
}

RationalNumber& RationalNumber::setDenominator(int denominator)
{
	this->denominator = denominator;
	simplify();
	return *this;
}

void RationalNumber::simplify()
{
	int gcd = std::abs(std::gcd(numerator, denominator));
	if (gcd != 0) {
		numerator /= gcd;
		denominator /= gcd;
	}
}

std::ostream& operator<<(std::ostream& out, const RationalNumber& obj)
{
	out << obj.numerator << "/" << obj.denominator;

	return out;
}

std::istream& operator>>(std::istream& in, RationalNumber& obj)
{
	int token;
	in >> token;
	obj.numerator=token;

	in.get();

	in >> token;
	obj.denominator=token;

	obj.simplify();
	return in;
}
