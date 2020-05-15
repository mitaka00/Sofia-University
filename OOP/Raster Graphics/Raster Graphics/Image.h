#pragma once
#include <string>
#include <fstream>
#include "ImageFormat.h"
#include "PPMFormat.h"
#include "PGMFormat.h"
#include "PBMFormat.h"

using string = std::string;

class Image
{
public:
	Image(const string name);

	void serialize(std::ofstream& out) const;
	void deserialize(std::ifstream& in);

	const string getName() const { return name; } ;

private:
	string name;
	ImageFormat* format;
};

