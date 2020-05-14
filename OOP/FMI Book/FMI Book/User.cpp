#include "User.h"

using std::string;

User::User(const std::string& username, int age) :
	username(username),
	age(age)
{
	blocked = false;
}

void User::rename(const std::string & newName)
{
	username = newName;
}

void User::addPost(const Post& currentPost)
{
	posts.push_back(currentPost);
}

void User::deletePost(const int id)
{
}
