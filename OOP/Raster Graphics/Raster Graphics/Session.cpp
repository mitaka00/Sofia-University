#include "Session.h"
#include <iostream>

unsigned Session::currentID = 0;

unsigned Session::getID()
{
	return currentID++;
}

Session::Session():
	id(getID())
{
}

void Session::addImage(const Image& image)
{
	images.push_back(image);
}


