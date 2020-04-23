#include "User.h"
#include <iostream>
#include <cstring>

User::User(const char* username, const char* password, const char* email):
	username(new char[strlen(username)+1]),
	password(new char[strlen(password) + 1]),
	email(new char[strlen(email) + 1])
{
	strcpy(this->username, username);
	strcpy(this->password, password);
	strcpy(this->email, email);
}

User::User(const User& other)
{
	copy(other);
}

User::User(std::ifstream& in)
{
	int len;
	in.read((char*)&len, sizeof(len));
	username = new char[len];
	in.read(username, len);

	in.read((char*)&len, sizeof(len));
	password = new char[len];
	in.read(password, len);

	in.read((char*)&len, sizeof(len));
	email = new char[len];
	in.read(email, len);
}

User& User::operator=(const User& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}

	return *this;
}

User::~User()
{
	clear();
}

void User::serialize(std::ofstream& out) const
{
	writeParam(username, out);
	writeParam(password, out);
	writeParam(email, out);
}

void User::readFriends(std::ifstream& in)
{
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
}

void User::writeFriends(std::ofstream& out) const
{
	int len = friends.size();
	out.write((const char*)&len, sizeof(len));
	for (int i = 0; i < len; i++)
	{
		int currentLength = friends[i].length() + 1;
		out.write((const char*)&currentLength, sizeof(currentLength));
		out.write((const char*)&friends[i][0], currentLength);
	}
}

void User::addFriend(const char* friendUser)
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

void User::clear()
{
	delete[] username;
	delete[] password;
	delete[] email;

	username = nullptr;
	password = nullptr;
	email = nullptr;
}

void User::copy(const User& other)
{
	username = new char [strlen(other.username) + 1];
	strcpy(username, other.username);

	password = new char [strlen(other.password) + 1];
	strcpy(password, other.password);

	email = new char [strlen(other.email) + 1];
	strcpy(email, other.email);

	friends = other.friends;
}

void User::writeParam(const char* param, std::ofstream& out) const
{
	int len = strlen(param) + 1;

	out.write((const char*)&len, sizeof(len));
	out.write((const char*)param, len);
}