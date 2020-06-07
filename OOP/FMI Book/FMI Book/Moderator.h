#pragma once
#include <string>
#include "User.h"
class Moderator: public User
{
public:
	Moderator(const std::string name="",int age=0);
	virtual ~Moderator() = default;
protected:
};

