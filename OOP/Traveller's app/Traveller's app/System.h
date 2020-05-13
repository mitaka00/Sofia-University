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
	void addFriend(const string& name);
	void addDestination();
	bool checkImageName(const string& name);
	void searchDestination(const string& destinationName);

	void run();

private:
	System();

	User currentUser;
	std::vector<User> users;				//All users
	std::vector<std::string> destinations;	//All destinations
	bool logged;

	void start();
	
	void readUsersFile(const string& fileName);
	void writeUsersFile(const string& fileName) const;	
	bool loginUser();
	bool registerUser();
	
	void readDestinationsFile(const string& fileName);
	void writeDestinationsFile(const string& fileName);
	Destination inputDestination();
	double calculateAverageGrade(const string& destinationName);
};

