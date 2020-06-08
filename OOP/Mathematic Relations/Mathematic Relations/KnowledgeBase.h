#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "BinaryRelation.h"

template <typename T, typename U>
class KnowledgeBase
{
public:
	void addMember(const std::string& name, const BinaryRelation<T, U>& currentRelation);
	void addRelation(const T& arg1, const U& arg2);
	BinaryRelation<T, U> kb(const std::string& name) const;
	std::vector<T> dom() const;
	std::vector<U> ran() const;
	void function() const;
	void injection() const;

	inline bool operator()(const T& arg1, const U& arg2) const;
	std::vector<T> operator()(U u) const;
	std::vector<U> operator[](T t) const;
	KnowledgeBase<U, T> operator!() const;

	// Algebraic assignment operators
	KnowledgeBase<T, U>& operator+=(const KnowledgeBase<T, U>& other);
	KnowledgeBase<T, U>& operator^=(const KnowledgeBase<T, U>& other);

	// Algebraic operators
	KnowledgeBase<T, U> operator+(const KnowledgeBase<T, U>& other) const;
	KnowledgeBase<T, U> operator^(const KnowledgeBase<T, U>& other) const;


	template<typename Tt, typename Uu>
	friend std::ostream& operator<<(std::ostream& out, const KnowledgeBase<Tt, Uu>& obj);

private:
	std::vector<std::pair<std::string, BinaryRelation<T, U>>> members;
};


#include "KnowledgeBase.ipp"