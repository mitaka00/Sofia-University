#pragma once
#include <vector>
#include "Image.h"
class Session
{
public:
	Session();

	void addImage(const Image& image);
private:
	unsigned int id;
	std::vector<Image> images;

	static unsigned getID();
	static unsigned int currentID;
};

