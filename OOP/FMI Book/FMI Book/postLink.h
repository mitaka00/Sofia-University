#pragma once
#include "Post.h"
#include <string>
class PostLink:public Post
{
public:
	PostLink(const std::string& content,const std::string& href);
	virtual ~PostLink() = default;

	virtual void serialize(std::ofstream& out) const override;
private:
	std::string href;
};

