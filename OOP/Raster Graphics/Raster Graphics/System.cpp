#include <iostream>
#include <cstring>
#include <stdio.h> 
#include <string.h> 
#include "System.h"
#include "Session.h"

const int MAX_CMD_LEN = 1024;
const int MAX_INPUT_LEN = 128;

System::System()
{
}

System& System::i()
{
	static System instance;
	return instance;
}

void System::printHelp() const
{
	std::cout << " The following commands are suported: " << std::endl
		<< "\tload <file> <file> ...		load files in session" << std::endl
		<< "\tclose		close current session" << std::endl
		<< "\tsave		saves files in current session" << std::endl
		<< "\tsaveas <file>		saves the first loaded file in <file>" << std::endl
		<< "\thelp		prints this information" << std::endl
		<< "\texit		exists the program" << std::endl;
}

System::~System()
{
	std::cout << "Have a nice day!" << std::endl;
}

void System::run()
{
	printHelp();

	char command[MAX_CMD_LEN];

	for (;;) {
		std::cin >> command;
		if (strcmp(command, "load") == 0) {
			Session currentSession=Session();
			readImages(currentSession);
		}
		else if (strcmp(command, "help") == 0) {
			printHelp();
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
		else {
			std::cout << "Unknown command! Type 'help' for available commands." << std::endl;
		}
	}
}


void System::readImages(Session& currentSession)
{
	char input[MAX_CMD_LEN];
	std::cin.getline(input, MAX_CMD_LEN);
	char* token;
	char* rest = input;
	while ((token = strtok_s(rest, " ", &rest))) {

		Image currentImage(token);
		if (currentImage.getFormat() == -1) {
			std::cout << currentImage.getName() << " has incorrect format!\n";
		}
		else {
			currentSession.addImage(currentImage);
			std::cout << currentImage.getName() << " added to the session\n";
		}		
	}

}