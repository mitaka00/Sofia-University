#pragma once
#include <string>
#include <vector>
#include "Post.h"
class User
{
public:
	User(const std::string& username = "", int age = 1);

	void rename(const std::string& newName);
	void addPost(const Post& currentPost);
	virtual void deletePost(const int id);

protected:
	std::string username;
	int age;
	std::vector<Post> posts;
	bool blocked;
};

