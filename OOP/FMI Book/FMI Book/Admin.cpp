#include "Admin.h"
#include "User.h"

Admin::Admin(const std::string& username, int age):
	Moderator(username,age)
{
}

void Admin::addUser() const
{
	//TODO...
}

void Admin::removeUser() const
{
	//TODO..
}
