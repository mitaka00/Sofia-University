#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "System.h"

using std::string;

System::System()
{
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
		<< "\taddDestination - add destination to your destinations." << std::endl
		<< "\tfriends - shows all your friends info." << std::endl
		<< "\taddFriend <name> - add friend with that name" << std::endl
		<< "\tshowDestinations - shows info about your added destinations." << std::endl
		<< "\tsearch <destination name> - shows grades for this destination and average grade." << std::endl
		<< "\thelp - shows info about the commands." << std::endl
		<< "\tbye - terminates the program." << std::endl;
}

//End of the program
System::~System()
{
	std::cout << "Have a nice day!" << std::endl;
}

//All operations you can use
void System::run()
{
	printHelp();

	string input;

	for (;;) {
		std::getline(std::cin, input);
		if (input == "addDestination") {
			
		}
		else if (input == "addFriend") {
			
		}
		else if (input == "friends") {
			
		}
		else if (input == "help") {
			printHelp();
		}
		else if (input == "bye") {
			break;
		}
		else {
			std::cout << "Unknown command! Type 'help' for available commands." << std::endl;
		}
	}
}