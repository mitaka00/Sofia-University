#pragma once
#include <iostream>
#include <fstream>
#include <string>
class Post
{
public:
	Post(const std::string& content);
	virtual ~Post() = default;

	virtual void serialize(std::ofstream& out) const = 0;

	int getId() const { return id; };
protected:
	std::string content;
	int id;
private:
	static unsigned getID();
	static unsigned currID;
};

