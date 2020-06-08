#pragma once

#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <tuple>

template <typename T,typename U>
class BinaryRelation
{
public:
	//Methods
	void addRelation(const T& arg1,const U& arg2);
	std::vector<T> dom() const;
	std::vector<U> ran() const;
	bool function() const;
	bool injection() const;

	inline bool operator()(const T& arg1, const U& arg2) const;
	std::vector<T> operator()(U u) const;
	std::vector<U> operator[](T t) const;
	BinaryRelation<U,T> operator!() const;

	// Algebraic assignment operators
	BinaryRelation<T, U>& operator+=(const BinaryRelation<T, U>& other);
	BinaryRelation<T, U>& operator^=(const BinaryRelation<T, U>& other);
	BinaryRelation<T, U>& operator*=(const BinaryRelation<U, U>& other);

	// Algebraic operators
	BinaryRelation<T,U> operator+(const BinaryRelation<T,U>& other) const;
	BinaryRelation<T, U> operator^(const BinaryRelation<T, U>& other) const;
	BinaryRelation<T, U> operator*(const BinaryRelation<U, U>& other) const;

	
	template<typename Tt, typename Uu>
	friend std::ostream& operator<<(std::ostream& out, const BinaryRelation<Tt,Uu>& obj);
	template<typename Tt, typename Uu>
	friend std::istream& operator>>(std::istream& in, BinaryRelation<T, U>& obj);
private:
	std::vector<std::pair<T,U>> relations;
};

#include "BinaryRelation.ipp"