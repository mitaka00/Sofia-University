#include "User.h"
#include <iostream>
#include <fstream>

using std::string;

User::User(const std::string& username, int age) :
	username(username),
	age(age)
{
	blocked = false;
}

User::~User()
{
	deletePosts();
}

void User::rename(const std::string & newName)
{
	username = newName;
}

void User::addPost(Post* currentPost)
{
	posts.push_back(currentPost);
}

void User::deletePost(const int id)
{
	for (int i = 0; i < posts.size(); i++)
	{
		if (posts[i]->getId() == id) {
			delete posts[i];
			posts.erase(posts.begin() + i);
			break;
		}
	}
}

void User::deletePosts()
{
	for (int i = 0; i < posts.size(); i++)
	{
		delete posts[i];
	}
	posts.clear();
}

void User::showPost(const int id) const
{
	std::ofstream out(username + "_" + std::to_string(id) + ".html");
	if (!out) {
		std::cout << "File can not be created\n";
	}
	else {
		out << "<!DOCTYPE html>" << std::endl;
		out << "<html>" << std::endl;
		out << "<body>" << std::endl;

		for (int i = 0; i < posts.size(); i++)
		{
			if (posts[i]->getId() == id) {
				posts[i]->serialize(out);
				break;
			}
		}

		out << "</html>" << std::endl;
		out << "</body>" << std::endl;
		out.close();
	}
}

void User::showAllPosts() const
{
	std::ofstream out(username + "_allPosts" + + ".html");
	if (!out) {
		std::cout << "File can not be created\n";
	}
	else {
		out << "<!DOCTYPE html>" << std::endl;
		out << "<html>" << std::endl;
		out << "<body>" << std::endl;

		for (int i = 0; i < posts.size(); i++)
		{
			posts[i]->serialize(out);
		}

		out << "</html>" << std::endl;
		out << "</body>" << std::endl;
		out.close();
	}
}

bool User::searchPost(const int id) const
{
	for (int i = 0; i < posts.size(); i++)
	{
		if (posts[i]->getId() == id) {
			return true;
		}
	}
	return false;
}
