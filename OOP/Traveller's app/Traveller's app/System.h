#pragma once
#include <iostream>
#include <vector>
#include "User.h"
#include "Destination.h"

class System
{
public:
	static System& i();
	System(const System&) = delete;
	void operator=(const System&) = delete;
	~System();

	bool loginUser();
	bool registerUser();

	void printHelp() const;

	void run();

private:
	System();

	void start();

	void readUsersFile(const char* fileName);
	void writeUsersFile(const char* fileName) const;
	void readFriendsFile(const char* fileName);
	void writeFriendsFile(const char* fileName) const;

	std::vector<User> users;
	User currentUser;

	std::vector<Destination> destinations;
	bool logged;
};

