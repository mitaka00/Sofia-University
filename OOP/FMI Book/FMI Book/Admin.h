#pragma once
#include "Moderator.h"
#include "User.h"
class Admin:public Moderator
{
public:
	Admin(const std::string& username = "", int age = 1);
	void addUser()const;
	void removeUser()const;
protected:
};
