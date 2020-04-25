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

	void printHelp() const;
	void addFriend(const char* name);

	void run();

private:
	System();

	bool logged;
	void start();

	std::vector<User> users;
	void readUsersFile(const char* fileName);
	void writeUsersFile(const char* fileName) const;	
	bool loginUser();
	bool registerUser();
	User currentUser;

	std::vector<std::string> destinations;
	void readDestinationsFile(const char* fileName);
	void writeDestinationsFile(const char* fileName);
};

