#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Post.h"
class User
{
	using string = std::string;
public:
	User(const string& username = "", int age = 1);
	~User();

	void rename(const string& newName);
	void addPost(Post* currentPost);
	virtual void deletePost(const int id);
	void deletePosts();
	void showPost(const int id) const;
	void showAllPosts() const;
	bool searchPost(const int id) const;

	void getBlocked() { blocked = true; };
	void getUnblocked() { blocked = false; };

	inline bool isBlocked()const { return blocked; };
	inline string getUsername() const  { return username; };
	inline int getAge() const { return age; };
	inline int getPostsCount() const { return posts.size(); };
protected:
	string username;
	int age;
	std::vector<const Post*> posts;
	bool blocked;
};

