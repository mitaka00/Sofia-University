#include "User.h"
#include <iostream>
#include <cstring>

const int MAX_TOKEN_LENGTH = 30;

User::User(const string username, const string password, const string email):
	username(username),
	password(password),
	email(email)
{}

User::User(const User& other)
{
	copy(other);
}

User::User(std::ifstream& in)
{
	int len;
	in.read((char*)&len, sizeof(len));
	username.resize(len);
	in.read((char*)&username[0], len);

	in.read((char*)&len, sizeof(len));
	password.resize(len);
	in.read((char*)&password[0], len);

	in.read((char*)&len, sizeof(len));
	email.resize(len);
	in.read((char*)&email[0], len);
}

User& User::operator=(const User& other)
{
	if (this != &other) {
		copy(other);
	}

	return *this;
}

void User::serialize(std::ofstream& out) const
{
	writeParam(username, out);
	writeParam(password, out);
	writeParam(email, out);
}

void User::readFriends()
{
	string token = username;

	std::ifstream in(token+"Friends.db", std::ios::binary);
	if (!in) {
		std::cout << "error";
	}

	int friendsLength;
	in.read((char*)&friendsLength, sizeof(friendsLength));
	friends.resize(friendsLength);
	for (int i = 0; i < friendsLength; i++)
	{
		int currentLength;
		in.read((char*)&currentLength, sizeof(currentLength));
		friends[i].resize(currentLength);
		in.read((char*)&friends[i][0], currentLength);
	}

	in.close();
}

void User::writeFriends() const
{
	string token = username;

	std::ofstream out(token+"Friends.db", std::ios::binary);
	if (!out) {
		std::cout << "error";
	}

	int len = friends.size();
	out.write((const char*)&len, sizeof(len));
	for (int i = 0; i < len; i++)
	{
		int currentLength = friends[i].length() + 1;
		out.write((const char*)&currentLength, sizeof(currentLength));
		out.write((const char*)&friends[i][0], currentLength);
	}

	out.close();
}

void User::addFriend(const string friendUser)
{
	friends.push_back(friendUser);
}

void User::showFriends() const
{
	int length = friends.size();
	for (int i = 0; i < length; i++)
	{
		std::cout << friends[i] <<" ";
	}
	std::cout << std::endl;
}

void User::addDestination(const Destination& currentDestination)
{
	destinations.push_back(currentDestination);
}

void User::serializeDestinations() const
{
	string token = username;
	std::ofstream out(token + ".db", std::ios::binary);
	if (!out) {
		std::cout << "Error";
	}

	int len = destinations.size();
	out.write((const char*)&len, sizeof(len));
	for (int i = 0; i < len; i++)
	{
		destinations[i].serialize(out);
	}

	out.close();
}

void User::copy(const User& other)
{
	username = other.username;
	password = other.password;
	email = other.email;
	friends = other.friends;
	destinations = other.destinations;
}

void User::writeParam(const string param, std::ofstream& out) const
{
	int len = param.length();

	out.write((const char*)&len, sizeof(len));
	out.write((const char*)&param[0], len);
}