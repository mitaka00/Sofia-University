#include "PostText.h"

PostText::PostText(const std::string& content):
	Post(content)
{}

void PostText::serialize(std::ofstream& out) const
{
	out << "<p>" + content + "</p>" << std::endl;
}