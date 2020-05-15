#include "Post.h"
#include<string>

unsigned Post::currID = 0;


unsigned Post::getID()
{
	return currID++;
}

Post::Post(const std::string& content):
	id(getID()),
	content(content)
{}