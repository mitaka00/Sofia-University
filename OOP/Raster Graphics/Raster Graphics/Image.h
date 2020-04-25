#pragma once
#include <string>
#include <fstream>
#include "ImageFormat.h"
#include "PPMFormat.h"
#include "PGMFormat.h"
#include "PBMFormat.h"

enum Formats {
	Invalid=-1,
	PBMFormat,
	PGMFormat,
	PPMFormat
};

class Image
{
	using string = std::string;
public:
	Image(const char* name);
	Image(std::ifstream& in);

	void serialize(std::ofstream& out) const;

	const string getName() const { return name; } ;
	const string getExtension() const { return extension; };
	const int getFormat() const { return format; };

private:
	string name;
	string extension;
	Formats format;
};

