#include "BinaryRelation.h"

using std::string;

template <typename T, typename U>
void BinaryRelation<T, U>::addRelation(const T& arg1,const U& arg2)
{
	if (!this->operator()(arg1,arg2)) {
		relations.push_back(std::make_pair(arg1, arg2));
	}
}

template<typename T, typename U>
std::vector<T> BinaryRelation<T, U>::dom() const
{
	std::vector<T> result;
	for (int i = 0; i < relations.size(); i++)
	{
		bool isContained = false;
		for (int y = 0; y < result.size(); y++)
		{
			if (result[y] == relations[i].first) {
				isContained = true;
				break;
			}
		}

		if (!isContained) {
			result.push_back(relations[i].first);
		}
		
	}
	return result;
}

template<typename T, typename U>
std::vector<U> BinaryRelation<T, U>::ran() const
{
	std::vector<U> result;
	for (int i = 0; i < relations.size(); i++)
	{
		bool isContained = false;
		for (int y = 0; y < result.size(); y++)
		{
			if (result[y] == relations[i].second) {
				isContained = true;
				break;
			}
		}

		if (!isContained) {
			result.push_back(relations[i].second);
		}
	}
	return result;
}

template<typename T, typename U>
bool BinaryRelation<T, U>::function() const
{
	for (int i = 0; i < relations.size(); i++)
	{
		for (int j = i + 1; j < relations.size(); j++)
		{
			if (relations[i].first == relations[j].first) {
				return false;
			}
		}
	}
	return true;
}

template<typename T, typename U>
bool BinaryRelation<T, U>::injection() const
{
	for (int i = 0; i < relations.size(); i++)
	{
		for (int j = i+1; j < relations.size(); j++)
		{
			if (relations[i].first != relations[j].first) {
				if (relations[i].second == relations[j].second) {
					return false;
				}
			}
		}
	}
	return true;
}

template<typename T, typename U>
bool BinaryRelation<T, U>::operator()(const T& arg1, const U& arg2) const
{
	for (int i = 0; i < relations.size(); i++)
	{
		if (relations[i].first == arg1 && relations[i].second == arg2) {
			return true;
		}
	}

	return false;
}

template<typename T, typename U>
std::vector<T> BinaryRelation<T, U>::operator()(U u) const
{
	std::vector<T> result;
	for (int i = 0; i < relations.size(); i++)
	{
		if (relations[i].second == u) {
			result.push_back(relations[i].first);
		}
	}
	return result;
}

template<typename T, typename U>
std::vector<U> BinaryRelation<T, U>::operator[](T t) const
{
	std::vector<U> result;
	for (int i = 0; i < relations.size(); i++)
	{
		if (relations[i].first == t) {
			result.push_back(relations[i].second);
		}
	}
	return result;
}

template<typename T, typename U>
BinaryRelation<U, T> BinaryRelation<T, U>::operator!() const
{
	BinaryRelation<U, T> other;
	for (int i = 0; i < relations.size(); i++)
	{
		other.addRelation(relations[i].second, relations[i].first);
	}
	return other;
}

template<typename T, typename U>
BinaryRelation<T, U>& BinaryRelation<T, U>::operator+=(const BinaryRelation<T, U>& other)
{
	for (int i = 0; i < other.relations.size(); i++)
	{
		addRelation(other.relations[i].first, other.relations[i].second);
	}
	return *this;
}

template<typename T, typename U>
BinaryRelation<T, U>& BinaryRelation<T, U>::operator^=(const BinaryRelation<T, U>& other)
{
	BinaryRelation<T, U> result;
	for (int i = 0; i < relations.size(); i++)
	{
		if (other(relations[i].first, relations[i].second)) {
			result.addRelation(relations[i].first, relations[i].second);
		}
	}

	relations = result.relations;
	return *this;
}

template<typename T, typename U>
BinaryRelation<T, U>& BinaryRelation<T, U>::operator*=(const BinaryRelation<U, U>& other)
{
	BinaryRelation<T, U> result;
	for (int i = 0; i < relations.size(); i++)
	{
		std::vector<U> tokenVector = other[relations[i].second];
		
		for (int j = 0; j < tokenVector.size(); j++)
		{
			result.addRelation(relations[i].first, tokenVector[j]);
		}
	}

	relations = result.relations;
	return *this;
}

template<typename T, typename U>
BinaryRelation<T, U> BinaryRelation<T, U>::operator+(const BinaryRelation<T,U>& other) const
{
	return BinaryRelation<T,U>(*this) += other;
}

template<typename T, typename U>
BinaryRelation<T, U> BinaryRelation<T, U>::operator^(const BinaryRelation<T, U>& other) const
{
	return BinaryRelation<T, U>(*this) ^= other;
}

template<typename T, typename U>
inline BinaryRelation<T, U> BinaryRelation<T, U>::operator*(const BinaryRelation<U, U>& other) const
{
	return BinaryRelation<T, U>(*this) *= other;
}

template<typename Tt, typename Uu>
std::ostream& operator<<(std::ostream& out,const BinaryRelation<Tt, Uu>& obj) {
	if (obj.relations.size() == 0) {
		out << "Pairs: { }\n";
	}
	else {
		out << "Pairs: {";
		for (int i = 0; i < obj.relations.size() - 1; i++)
		{
			out << "(" << obj.relations[i].first << ", " << obj.relations[i].second << "), ";
		}
		out << "(" << obj.relations[obj.relations.size() - 1].first << ", " << obj.relations[obj.relations.size() - 1].second << ")}\n";
	}
	return out;
}

template<typename Tt, typename Uu>
std::istream& operator>>(std::istream& in, const BinaryRelation<Tt, Uu>& obj) {
	string token;
	std::getline(std::cin, token);
	if (token[0] == '(' && token[token.size() - 1] == ')') {
		token = token.substr(1);
		token.pop_back();
		
		int index = token.find(", ");
		if (index == -1) {
			std::cout << "Invalid input\n";
		}
		else {
			string firstParam = token.substr(0, index);
			string secondParam = token.substr(index + 2);

			//TODO implement logic for all data types
		}		
	}
	else {
		std::cout << "Invalid input\n";
	}

	return in;
}