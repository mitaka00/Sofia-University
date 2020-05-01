#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Destination.h"

using string = std::string;
class User
{
public:
	User(const string username="", const string password="", const string email="");
	User(std::ifstream& in);
	void serialize(std::ofstream& out) const;

	void readFriends();
	void writeFriends() const;
	void addFriend(const string friendUser);
	void showFriendsInfo() const;
	bool includeFriend(const string name) const;

	void addDestination(const Destination& currentDestination);
	void writeDestinations() const;
	void readDestinations();
	void showDestinations() const;

	inline string getUsername() const { return username; };
	inline string getEmail() const { return email; };
	inline string getPassword() const { return password; };

private:
	string username;
	string password;
	string email;
	std::vector<std::string> friends;
	std::vector<Destination> destinations;

	void writeParam(const string param, std::ofstream& out) const;
};

