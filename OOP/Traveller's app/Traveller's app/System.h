#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Destination.h"

using string = std::string;
class System
{
public:
	static System& i();
	System(const System&) = delete;
	void operator=(const System&) = delete;
	~System();

	void printHelp() const;
	void addFriend(const char* name);
	void addDestination();

	void run();

private:
	System();

	User currentUser;
	std::vector<User> users;
	std::vector<std::string> destinations;
	bool logged;

	void start();
	
	void readUsersFile(const char* fileName);
	void writeUsersFile(const char* fileName) const;	
	bool loginUser();
	bool registerUser();
	
	void readDestinationsFile(const string fileName);
	void writeDestinationsFile(const string fileName);
	const Destination inputDestination();
};

