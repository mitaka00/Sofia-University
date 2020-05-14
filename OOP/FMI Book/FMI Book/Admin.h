#pragma once
#include "Moderator.h"
class Admin:public Moderator
{
public:
	void addUser()const;
	void removeUser()const;
protected:
};

