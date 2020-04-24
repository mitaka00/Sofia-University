#include "Image.h"
const int MAX_IMAGE_LENGTH = 30;
using string = std::string;

Image::Image(const char* name)
{
	char token[MAX_IMAGE_LENGTH];
	strcpy(token, name);
	char* secondToken = strtok(token, ".");
	this->name = secondToken;
	secondToken = strtok(nullptr, ".");
	extension = secondToken;

	if (extension == "ppm") {
		format=PPMFormat;
	}
	else if (extension == "pgm") {
		format = PGMFormat;
	}
	else if (extension == "pbm") {
		format = PBMFormat;
	}
	else {
		format = Invalid;
	}
}

Image::Image(std::ifstream& in)
{
	
}

void Image::serialize(std::ofstream& out) const
{
}
