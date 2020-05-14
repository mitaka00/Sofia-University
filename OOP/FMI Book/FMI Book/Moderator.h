#pragma once
#include <string>
#include "User.h"
class Moderator: public User
{
public:
	Moderator(const std::string name="",int age=0);

	virtual void deletePost(const int id)override ;
	void blockUser()const;
	void unblockUser()const;
protected:

};

