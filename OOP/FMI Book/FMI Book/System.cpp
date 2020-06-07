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
		<< "\t<actor> view_post <Id> - view Post with that id." << std::endl
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

		if (token.size() == 4 && (token[1] == "add_user" || token[1] == "add_moderator" )) {
			createUser(token);
		}
		else if (token.size() == 3 && token[1] == "remove_user"){
			removeUser(token);
		}
		else if (token.size() == 3 && token[1] == "rename") {
			renameUser(token);
		}
		else if (token.size() == 3 && token[1] == "block") {
			blockUser(token);
		}
		else if (token.size() == 3 && token[1] == "unblock") {
			unblockUser(token);
		}
		else if (token.size() == 4 && token[1] == "post" && token[2]=="[image]") {
			postImage(token);
		}
		else if (token.size() == 4 && token[1] == "post" && token[2] == "[text]") {
			postText(token);
		}
		else if (token.size() == 5 && token[1] == "post" && token[2] == "[url]") {
			postLink(token);
		}
		else if (token.size() == 3 && token[1] == "remove_post") {
			removePost(token);
		}
		else if (token.size() == 3 && token[1] == "view_post") {
			viewPost(token);
		}
		else if (token.size() == 3 && token[1] == "view_all_posts") {
			viewAllPosts(token);
		}
		else if (input == "info") {
			showInfo();
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
}

void System::blockUser(const std::vector<string>& token)
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

void System::unblockUser(const std::vector<string>& token)
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
					users[index]->getUnblocked();
					cout << token[0] << " unblocked " << token[2] << std::endl;
				}
			}
			else {
				cout << "This user doesn't have permission\n";
			}
		}
	}
}

void System::renameUser(const std::vector<string>& token)
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

void System::createUser(const std::vector<string>& token)
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
		cout << "Only " + users[0]->getUsername() + " can do this!\n";
	}
}

void System::removeUser(const std::vector<string>& token)
{
	if (token[2] == users[0]->getUsername()) {
		cout << "Admin can't be removed\n";
	}
	else {
		if (token[0] == users[0]->getUsername()) {
			int index = checkUser(token[2]);
			if (index == -1) {
				cout << "No user with that name\n";
			}
			else {
				users[index]->deletePosts();
				delete users[index];
				users.erase(users.begin()+index);

				cout << token[2] << " removed\n";

			}
		}
		else {
			cout << "Only Admin can do this!\n";
		}
	}
	
}

void System::postImage(const std::vector<string>& token)
{
	int index = checkUser(token[0]);
	if (index == -1) {
		cout << "No user with that name\n";
	}
	else {
		if (users[index]->isBlocked()) {
			cout << token[0] << " is blocked and can't post anything.\n";
		}
		else {
			users[index]->addPost(new PostImage(token[3]));
			cout << "Image posted\n";
		}
	}
}

void System::postText(const std::vector<string>& token)
{
	int index = checkUser(token[0]);
	if (index == -1) {
		cout << "No user with that name\n";
	}
	else {
		if (users[index]->isBlocked()) {
			cout << token[0] << " is blocked and can't post anything.\n";
		}
		else {
			users[index]->addPost(new PostText(token[3]));
			cout << "Text posted\n";
		}
	}
}

void System::postLink(const std::vector<string>& token)
{
	int index = checkUser(token[0]);
	if (index == -1) {
		cout << "No user with that name\n";
	}
	else {
		if (users[index]->isBlocked()) {
			cout << token[0] << " is blocked and can't post anything.\n";
		}
		else {
			users[index]->addPost(new PostLink(token[4], token[3]));
			cout << "Link posted\n";
		}
	}
}

void System::removePost(const std::vector<string>& token)
{
	int index = checkUser(token[0]);
	if (index == -1) {
		cout << "No user with that name\n";
	}
	else {
		bool searchPost = false;
		int searchingId = stoi(token[2]);
		for (int i = 0; i < users.size(); i++)
		{
			searchPost = users[i]->searchPost(searchingId);
			if (searchPost) {
				if (typeid(*users[index])==typeid(Admin) //Admin delete post
					|| (typeid(*users[index]) == typeid(Moderator) && typeid(*users[i]) == typeid(User)) //Moderator delete User post
					|| index == i) //User delete own post
				{
					users[i]->deletePost(searchingId);
					cout << "Post is deleted\n";
				}
				else {
					cout << "No permission\n";
				}
				break;
			}
		}

		if (!searchPost) {
			cout << "No post with id=" << searchingId << std::endl;
		}
	}
}

void System::viewPost(const std::vector<string>& token) const
{
	int index = checkUser(token[0]);
	if (index == -1) {
		cout << token[0] << " is not in database\n";
	}
	else {
		bool searchPost = false;
		int searchingId = stoi(token[2]);
		for (int i = 0; i < users.size(); i++)
		{
			searchPost = users[i]->searchPost(searchingId);
			if (searchPost) {
				users[i]->showPost(searchingId);
				cout << "File with id:" << searchingId << " is created\n";
				break;
			}
		}

		if (!searchPost) {
			cout << "No post with id=" << searchingId << std::endl;
		}
	}
}

void System::viewAllPosts(const std::vector<string>& token) const
{
	int index = checkUser(token[0]);
	if (index == -1) {
		cout << token[0] << " is not in database\n";
	}
	else {
		index = checkUser(token[2]);
		if (index == -1) {
			cout << token[2] << " is not in database\n";
		}
		else {
			users[index]->showAllPosts();
			cout << "File with posts is created\n";
		}
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

void System::showInfo() const
{
	std::vector<int> blockedUsersIndexes;
	int indexOfTheYoungestUser = 0;
	int indexOfTheOldestUser = 0;

	cout << "There are " + std::to_string(users.size()) + " users:\n";
	for (int i = 0; i < users.size(); i++)
	{
		//Print Info for every user in database
		printUserInfo(i);

		//Check Info for Blocked Users
		if (users[i]->isBlocked()) {
			blockedUsersIndexes.push_back(i);
		}

		//Check info about the youngest and the oldest user
		checkYoungestAndOldestInfo(i, indexOfTheOldestUser, indexOfTheYoungestUser);
	}

	//Print blocked Users
	if (blockedUsersIndexes.size() == 0) {
		cout << "There aren't any blocked users.\n";
	}
	else {
		cout << "Blocked Users:\n";
		for (int i = 0; i < blockedUsersIndexes.size(); i++)
		{
			cout << users[blockedUsersIndexes[i]]->getUsername() << std::endl;
		}
	}

	//Print youngest and oldest user
	if (indexOfTheOldestUser == 0) {
		cout << "Admin is the only user in this application\n";
	}
	else {
		cout << "oldest " << users[indexOfTheOldestUser]->getUsername() << " " << users[indexOfTheOldestUser]->getAge() << std::endl;
		cout << "youngest " << users[indexOfTheYoungestUser]->getUsername() << " " << users[indexOfTheYoungestUser]->getAge() << std::endl;
	}
}

void System::printUserInfo(const int index) const
{
	cout << users[index]->getUsername() + " - ";
	if (typeid(*users[index]) == typeid(User)) {
		cout << "User, ";
	}
	else if (typeid(*users[index]) == typeid(Moderator)) {
		cout << "Moderator, ";
	}
	else {
		cout << "Administrator, ";
	}

	cout << users[index]->getPostsCount() << " posts.\n";
}

void System::checkYoungestAndOldestInfo(int index, int& indexOfTheOldestUser, int& indexOfTheYoungestUser) const
{
	if (index == 1) {
		indexOfTheOldestUser = 1;
		indexOfTheYoungestUser = 1;
	}
	else {
		if (users[index]->getAge() > users[indexOfTheOldestUser]->getAge()) {
			indexOfTheOldestUser = index;
		}
		if (users[index]->getAge() < users[indexOfTheYoungestUser]->getAge()) {
			indexOfTheYoungestUser = index;
		}
	}
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