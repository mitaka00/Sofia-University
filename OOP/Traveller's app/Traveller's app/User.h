#pragma once
#include <fstream>
#include <vector>
#include <string>
class User
{
public:
	User(const char* username="", const char* password="", const char* email="");
	User(const User& other);
	User(std::ifstream& in);
	User& operator=(const User& other);
	~User();
	void serialize(std::ofstream& out) const;

	void readFriends(std::ifstream& in);
	void writeFriends(std::ofstream& out) const;
	void addFriend(const char* friendUser);
	void showFriends() const;

	inline const char* getUsername() const { return username; };
	inline const char* getEmail() const { return email; };
	inline const char* getPassword() const { return password; };

private:
	char* username;
	char* password;
	char* email;
	std::vector<std::string> friends;

	void clear();
	void copy(const User& other);
	void writeParam(const char* param, std::ofstream& out) const;
};

