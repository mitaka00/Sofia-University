#include "postLink.h"

PostLink::PostLink(const std::string& content, const std::string& href):
	Post(content),
	href(href)
{}

void PostLink::serialize(std::ofstream& out) const
{
	out << "<a href = \"" + href +"\">" + content +"</a>" << std::endl;
}