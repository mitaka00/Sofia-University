#pragma once
#include <string>
class Post
{
public:
	Post(const std::string& content);
protected:
	std::string content;
	int id;
private:
	static unsigned getID();
	static unsigned currID;
};

