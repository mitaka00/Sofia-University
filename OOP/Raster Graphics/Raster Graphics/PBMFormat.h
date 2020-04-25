#pragma once
#include "ImageFormat.h"
#include <vector>
#include <fstream>
class PBMFormat:public ImageFormat
{
public:
	PBMFormat(int width = 0, int height = 0);

	void serialize(std::ofstream& out) const;
	
private:
	std::vector<std::vector<int>> matrix;
};

