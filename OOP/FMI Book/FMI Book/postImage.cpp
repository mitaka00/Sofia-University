#include "postImage.h"

PostImage::PostImage(const std::string& content):
	Post(content)
{}

void PostImage::serialize(std::ofstream& out) const
{
	out << "<img src = \"" + content +"\" alt = \"Italian Trulli\" >" << std::endl;
}
