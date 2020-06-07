#pragma once
#include "Post.h"
#include <string>
class PostText:public Post
{
public:
	PostText(const std::string& content);
	virtual ~PostText() = default;

	virtual void serialize(std::ofstream& out) const override;
private:
};

