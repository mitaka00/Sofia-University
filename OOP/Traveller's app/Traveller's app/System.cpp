#include <iostream>
#include <cstring>
#include "System.h"
#include "Date.h"

const int MAX_CMD_LEN = 15;
const int MAX_INPUT_LEN = 128;

System::System()
	: logged(false)
{
	start();
}

System& System::i()
{
	static System instance;
	return instance;
}

//Authentication
void System::start()
{
	char input[MAX_CMD_LEN];

	readUsersFile("users.db");
	readDestinationsFile("destinations.db");

	std::cout << "login/register" << std::endl;
	do {
		logged = false;
		std::cin >> input;

		if (strcmp(input, "register") == 0) {
			if (!registerUser()) {
				std::cout << "This email or username is already used. Please try again. register/login" << std::endl;
				continue;
			}
			logged = true;
			std::cout << "You are logged successfuly" << std::endl;
		}
		else if (strcmp(input, "login") == 0) {
			if (!loginUser()) {
				std::cout << "This username or password is incorrect used. Please try again. register/login" << std::endl;
				continue;
			}

			logged = true;
			std::cout << "You are logged successfuly" << std::endl;
		}
		else {
			std::cout << "Invalid command. Please try again!" << std::endl;
		}
	} while (!logged);

}

//Read all users from Database
void System::readUsersFile(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (!in) {
		std::cout << "No users database"<<std::endl;
	}
	else {
		int size = users.size();
		in.read((char*)&size, sizeof(size));
		users.reserve(size);

		for (int i = 0; i < size; i++)
		{
			User currentUser(in);
			users.push_back(currentUser);
		}
	}
	in.close();
}

//Save all users in Database
void System::writeUsersFile(const char* fileName) const
{
	std::ofstream out(fileName, std::ios::binary);
	if (!out) {
		std::cout << "error";
	}

	int size = users.size();
	out.write((char*)&size, sizeof(size));
	for (int i = 0; i < size; i++)
	{
		users[i].serialize(out);
	}

	out.close();
}

//Read all destinations in Database
void System::readDestinationsFile(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (!in) {
		std::cout << "No destinations database" << std::endl;
	}
	else {
		int size = destinations.size();
		in.read((char*)&size, sizeof(size));
		destinations.reserve(size);

		for (int i = 0; i < size; i++)
		{
			int currentLenght;
			in.read((char*)&currentLenght, sizeof(currentLenght));
			destinations[i].resize(currentLenght);
			in.read((char*)&destinations[i][0], currentLenght);
		}
	}
	in.close();
}

//Save all destinations in Database
void System::writeDestinationsFile(const char* fileName)
{
	std::ofstream out(fileName, std::ios::binary);
	if (!out) {
		std::cout << "error" << std::endl;
	}
	else {
		int size = destinations.size();
		out.write((char*)&size, sizeof(size));

		for (int i = 0; i < size; i++)
		{
			int currentLength = destinations[i].length() + 1;
			out.write((const char*)&currentLength, sizeof(currentLength));
			out.write((const char*)&destinations[i][0], currentLength);
		}
	}
	out.close();
}

//Register user in Database
bool System::registerUser()
{
	char username[MAX_INPUT_LEN];
	char password[MAX_INPUT_LEN];
	char email[MAX_INPUT_LEN];

	std::cout << "Username: ";
	std::cin >> username;
	std::cout << std::endl << "Password: ";
	std::cin >> password;
	std::cout << std::endl << "Email: ";
	std::cin >> email;

	for (int i = 0; i < users.size(); i++)
	{
		if ((strcmp(username, users[i].getUsername()) == 0) || (strcmp(email, users[i].getEmail()) == 0)) {
			return false;
		}
	}

	currentUser = User(username, password, email);
	currentUser.writeFriends();
	users.push_back(currentUser);

	//write in users file
	writeUsersFile("users.db");

	std::cout << "You are registered!!" << std::endl;

	return true;
}

//Login user
bool System::loginUser()
{
	char username[MAX_INPUT_LEN];
	char password[MAX_INPUT_LEN];

	std::cout << "Username: ";
	std::cin >> username;
	std::cout << std::endl << "Password: ";
	std::cin >> password;

	for (int i = 0; i < users.size(); i++)
	{
		if ((strcmp(username, users[i].getUsername()) == 0) && (strcmp(password, users[i].getPassword()) == 0)) {
			currentUser = users[i];
			currentUser.readFriends();

			return true;
		}
	}

	return false;
}

//Show all functions you can use
void System::printHelp() const
{
	std::cout << " - List of commands - " << std::endl
		<< "\tcreate <departure> <destination> <money> - Create flight." << std::endl
		<< "\tfriends - shows all your friends." << std::endl
		<< "\taddFriend <name> - add friend with that name" << std::endl
		<< "\thelp - shows info about the commands." << std::endl
		<< "\tbye - terminates the program." << std::endl;
}

//Add friend to your friend list
void System::addFriend(const char* friendName)
{
	bool isTrue = false;
	int length = users.size();
	for (int i = 0; i < length; i++)
	{
		if (strcmp(users[i].getUsername(), friendName) == 0 && strcmp(friendName, currentUser.getUsername()) != 0) {
			isTrue = true;
			break;
		}
	}
	if (isTrue) {
		currentUser.addFriend(friendName);
		currentUser.writeFriends();
		std::cout << friendName << " added to your friend list" << std::endl;
	}
	else {
		std::cout << "No user with this name" << std::endl;
	}
}

System::~System()
{
	std::cout << "Have a nice day!" << std::endl;
}

//All operations you can use
void System::run()
{
	printHelp();

	char input[MAX_CMD_LEN];

	for (;;) {
		std::cin >> input;
		if (strcmp(input, "addDestination") == 0) {
			char destName[MAX_INPUT_LEN];
			int grade;
			Date startDate;
			Date endDate;
			char comment[MAX_INPUT_LEN];
			
			/*
			TODO...

			std::cout << "Enter destination name: ";
			std::cin >> destName;
			std::cout << std::endl << "Enter grade from 1 to 5: ";
			do {
				std::cin >> grade;
				if (grade < 1 || grade>5) {
					std::cout << std::endl << "Invalid grade. Please try again";
				}
			} while (grade < 1 || grade>5);
			std::cout << std::endl << "Enter start date [YYYY]-[MM]-[DD]: ";
			std::cin >> startDate;
			std::cout << std::endl << "Enter end date [YYYY]-[MM]-[DD]: ";
			std::cin >> endDate;
			if (!startDate || !endDate || endDate < startDate) {

			};*/
			
		}
		else if (strcmp(input, "addFriend") == 0) {
			char friendName[MAX_CMD_LEN];
			std::cin >> friendName;
			addFriend(friendName);
		}
		else if (strcmp(input, "friends") == 0) {
			currentUser.showFriends();
		}
		else if (strcmp(input, "help") == 0) {
			printHelp();
		}
		else if (strcmp(input, "bye") == 0) {
			break;
		}
		else {
			std::cout << "Unknown command! Type 'help' for available commands." << std::endl;
		}
	}
	
}