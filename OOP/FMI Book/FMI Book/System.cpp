#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "System.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;

System::System()
{
	users.push_back(new Admin("Admin"));
	cout << "Admin created\n";
}

System& System::i()
{
	static System instance;
	return instance;
}

//Show all functions you can use
void System::printHelp() const
{
	std::cout << " - List of commands - " << std::endl
		<< "\t<actor> add_moderator <name> <age>- add Moderator with that name and age." << std::endl
		<< "\t<actor> add_user <name> <age>- add User with that name and age." << std::endl
		<< "\t<actor> remove_user <name> - remove User or Moderator with that name." << std::endl
		<< "\t<actor> block <name> - block User or Moderator with that name." << std::endl
		<< "\t<actor> unblock <name> - unblock User or Moderator with that name." << std::endl
		<< "\t<actor> remove_post <Id> - remove Post with that id." << std::endl
		<< "\t<actor>view_post <Id> - view Post with that id." << std::endl
		<< "\t<actor> view_all_posts <name> - view all user's posts." << std::endl
		<< "\t<actor> post [image] <adress> - post image with that adress." << std::endl
		<< "\t<actor> post [url] <url> <text> - post link on that url with that text." << std::endl
		<< "\t<actor> post [text] <text> - post paragraph with that text." << std::endl
		<< "\t<actor> rename <name> - rename the actor." << std::endl
		<< "\tinfo - shows info about the users." << std::endl
		<< "\thelp - shows info about the commands." << std::endl
		<< "\tquit - terminates the program." << std::endl;
}

//End of the program
System::~System()
{
	for (int i = 0; i < users.size(); i++)
	{
		delete users[i];
	}

	std::cout << "Have a nice day!" << std::endl;
}

//All operations you can use
void System::run()
{
	printHelp();

	string input;

	for (;;) {
		std::getline(std::cin, input);
		vector<string> token = split(input, ' ');
		try {

			if (token[1] == "add_user" || token[1] == "add_moderator") {
				createUser(token);
			}
			else if (token[1] == "rename") {
				renameUser(token);
			}
			else if (token[1] == "block") {
				blockUser(token);
			}
			else if (token[1] == "unblock") {
				unblockUser(token);
			}
			else if (input == "help") {
				printHelp();
			}
			else if (input == "quit") {
				break;
			}
			else {
				std::cout << "Unknown command! Type 'help' for available commands." << std::endl;
			}

		}
		catch (const std::exception & e) {
			cout << e.what();
		}
	}
}

void System::blockUser(std::vector<string> token)
{
	if (token[2] == users[0]->getUsername()) {
		cout << "You can't block the Admin\n";
	}
	else {
		int index= checkUser(token[0]);
		if (index == -1) {
			cout << "No user with that name\n";
		}
		else {
			if (typeid(*users[index]) != typeid(User)) {
				index = checkUser(token[2]);
				if (index == -1) {
					cout << "No user with that name\n";
				}
				else {
					users[index]->getBlocked();
					cout << token[0] << " blocked " << token[2] << std::endl;
				}
			}
			else {
				cout << "This user doesn't have permission\n";
			}
		}
	}
}

void System::unblockUser(std::vector<string> token)
{
	if (token[2] == users[0]->getUsername()) {
		cout << "You can't unblock the Admin\n";
	}
	else {
		int index = checkUser(token[0]);
		if (index == -1) {
			cout << "No user with that name\n";
		}
		else {
			if (typeid(*users[index]) != typeid(User)) {
				index = checkUser(token[2]);
				if (index == -1) {
					cout << "No user with that name\n";
				}
				else {
					users[index]->getBlocked();
					cout << token[0] << " unblocked " << token[2] << std::endl;
				}
			}
			else {
				cout << "This user doesn't have permission\n";
			}
		}
	}
}

void System::renameUser(std::vector<string> token)
{
	int index = checkUser(token[2]);
	if (index == -1) {
		index = checkUser(token[0]);
		users[index]->rename(token[2]);
		cout << "User " << token[0] << " is now known as " << token[2] << std::endl;
	}
	else {
		cout << "Username have already used\n";
	}
}

void System::createUser(std::vector<string> token)
{
	if (token[0] == users[0]->getUsername()) {
		if (checkUser(token[2]) != -1) {
			cout << "User have already created\n";
		}
		else {
			if (token[1] == "add_user") {
				users.push_back(new User(token[2], stoi(token[3])));
			}
			else {
				users.push_back(new Moderator(token[2], stoi(token[3])));
			}
			cout << token[2] << " created\n";
		}
	}
	else {
		cout << "Only Admin can do this!\n";
	}
}

int System::checkUser(const string& name) const
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->getUsername() == name) {
			return i;
		}
	}

	return -1;
}

vector<string> System::split(const string& s, char delim)
{
	vector<string> result;
	std::stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}