#include <iostream>
#include <fstream>
#include <cstring>
#include "System.h"
#include "Session.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

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
	string command;

	for (;;) {
		std::cin >> command;
		if (command=="load") {
			Session currentSession=Session();
			readImages(currentSession);
		}
		else if (command=="help") {
			printHelp();
		}
		else if (command=="exit") {
			break;
		}
		else {
			std::cout << "Unknown command! Type 'help' for available commands." << std::endl;
		}
	}
}


void System::readImages(Session& currentSession)
{
	string input;
	std::cin.ignore();
	std::getline(cin, input);
	
	std::ifstream in(input);
	if (!in) {
		std::cout << "errorr\n";
	}
	else {
		Image currentImage(input);
	}
	in.close();
}