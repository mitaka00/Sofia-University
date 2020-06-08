#include "KnowledgeBase.h"

using std::cout;

template<typename T, typename U>
void KnowledgeBase<T, U>::addMember(const std::string& name, const BinaryRelation<T, U>& currentRelation)
{
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].first == name) {
			cout << "The name have already used\n";
			return;
		}
	}
	members.push_back(std::make_pair(name, currentRelation));
}

template<typename T, typename U>
void KnowledgeBase<T, U>::addRelation(const T& arg1, const U& arg2)
{
	for (int i = 0; i < members.size(); i++)
	{
		members[i].second.addRelation(arg1, arg2);
	}
}

template<typename T, typename U>
BinaryRelation<T, U> KnowledgeBase<T, U>::kb(const std::string& name) const
{
	for (int i = 0; i < members.size(); i++)
	{
		if (name == members[i].first) {
			return members[i].second;
		}
	}

	BinaryRelation<T, U> t;
	return t;
}

template<typename T, typename U>
std::vector<T> KnowledgeBase<T, U>::dom() const
{
	std::vector<T> result;

	for (int i = 0; i < members.size(); i++)
	{
		std::vector<T> token = members[i].second.dom();
		for (int j = 0; j < token.size(); j++)
		{
			
			bool isContained = false;
			for (int z = 0; z < result.size(); z++)
			{
				if (token[j] == result[z]) {
					isContained = true;
					break;
				}

			}

			if (!isContained) {
				result.push_back(token[j]);
			}
		}
	}

	return result;
}

template<typename T, typename U>
std::vector<U> KnowledgeBase<T, U>::ran() const
{
	std::vector<U> result;

	for (int i = 0; i < members.size(); i++)
	{
		std::vector<U> token = members[i].second.ran();
		for (int j = 0; j < token.size(); j++)
		{

			bool isContained = false;
			for (int z = 0; z < result.size(); z++)
			{
				if (token[j] == result[z]) {
					isContained = true;
					break;
				}

			}

			if (!isContained) {
				result.push_back(token[j]);
			}
		}
	}

	return result;
}

template<typename T, typename U>
void KnowledgeBase<T, U>::function() const
{
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].second.function()) {
			std::cout << members[i].first << " is a partial function\n";
		}
		else {
			std::cout << members[i].first << " is not a partial function\n";
		}
	}
}

template<typename T, typename U>
void KnowledgeBase<T, U>::injection() const
{
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].second.injection()) {
			std::cout << members[i].first << " is an injectable function\n";
		}
		else {
			std::cout << members[i].first << " is not an injectable function\n";
		}
	}
}

template<typename T, typename U>
bool KnowledgeBase<T, U>::operator()(const T& arg1, const U& arg2) const
{
	bool result;
	for (int i = 0; i < members.size(); i++)
	{
		result = members[i].second(arg1, arg2);
		if (result == true) {
			return true;
		}
	}

	return false;
}

template<typename T, typename U>
std::vector<T> KnowledgeBase<T, U>::operator()(U u) const
{
	std::vector<T> result;

	for (int i = 0; i < members.size(); i++)
	{
		std::vector<T> token = members[i].second(u);
		for (int j = 0; j < token.size(); j++)
		{

			bool isContained = false;
			for (int z = 0; z < result.size(); z++)
			{
				if (token[j] == result[z]) {
					isContained = true;
					break;
				}

			}

			if (!isContained) {
				result.push_back(token[j]);
			}
		}
	}

	return result;
}

template<typename T, typename U>
std::vector<U> KnowledgeBase<T, U>::operator[](T t) const
{
	std::vector<U> result;

	for (int i = 0; i < members.size(); i++)
	{
		std::vector<U> token = members[i].second[t];
		for (int j = 0; j < token.size(); j++)
		{

			bool isContained = false;
			for (int z = 0; z < result.size(); z++)
			{
				if (token[j] == result[z]) {
					isContained = true;
					break;
				}

			}

			if (!isContained) {
				result.push_back(token[j]);
			}
		}
	}

	return result;
}

template<typename T, typename U>
KnowledgeBase<U, T> KnowledgeBase<T, U>::operator!() const
{
	KnowledgeBase<U, T> other;
	for (int i = 0; i < members.size(); i++)
	{
		other.addMember(members[i].first, !members[i].second);
	}
	return other;
}

template<typename T, typename U>
KnowledgeBase<T, U>& KnowledgeBase<T, U>::operator+=(const KnowledgeBase<T, U>& other)
{
	for (int i = 0; i < other.members.size(); i++)
	{
		bool isContained = false;
		int index = -1;
		for (int j = 0; j < members.size(); j++)
		{
			if (other.members[i].first == members[j].first) {
				isContained = true;
				index = j;
				break;
			}
		}

		if (isContained) {
			members[index].second += other.members[i].second;
		}
		else {
			addMember(other.members[i].first, other.members[i].second);
		}
	}

	return *this;
}

template<typename T, typename U>
KnowledgeBase<T, U>& KnowledgeBase<T, U>::operator^=(const KnowledgeBase<T, U>& other)
{
	KnowledgeBase<T, U> result;
	for (int i = 0; i < members.size(); i++)
	{
		for (int j = 0; j < other.members.size(); j++)
		{
			if (members[i].first == other.members[j].first) {
				BinaryRelation<T, U> token;
				token += members[i].second ^ other.members[j].second;
				result.addMember(members[i].first, token);
			}
		}
	}

	members = result.members;
	return *this;
}

template<typename T, typename U>
KnowledgeBase<T, U> KnowledgeBase<T, U>::operator+(const KnowledgeBase<T, U>& other) const
{
	return KnowledgeBase<T, U>(*this) += other;
}

template<typename T, typename U>
KnowledgeBase<T, U> KnowledgeBase<T, U>::operator^(const KnowledgeBase<T, U>& other) const
{
	return KnowledgeBase<T, U>(*this) ^= other;
}

template<typename Tt, typename Uu>
std::ostream& operator<<(std::ostream& out, const KnowledgeBase<Tt, Uu>& obj) {
	if (obj.members.size() == 0) {
		std::cout << "KnowledgeBase is empty\n";
	}
	else {
		for (int i = 0; i < obj.members.size(); i++)
		{
			std::cout << obj.members[i].first << " " << obj.members[i].second;
		}
	}
	return out;
}
