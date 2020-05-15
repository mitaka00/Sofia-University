#pragma once
#include <string>
#include <vector>
#include "Post.h"
class User
{
	using string = std::string;
public:
	User(const string& username = "", int age = 1);

	void rename(const string& newName);
	void addPost(const Post& currentPost);
	virtual void deletePost(const int id);

	string getUsername() const  { return username; };

	void getBlocked() { blocked = true; };
	void getUnblocked() { blocked = false; };

protected:
	string username;
	int age;
	std::vector<Post> posts;
	bool blocked;
};

