#pragma once
#include "Post.h"
#include <string>
class PostImage:public Post
{
public:
	PostImage(const std::string& content);
	virtual ~PostImage() = default;

	virtual void serialize(std::ofstream& out) const override;
private:
};

