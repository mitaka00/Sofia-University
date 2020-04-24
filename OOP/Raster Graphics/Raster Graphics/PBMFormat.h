#pragma once
#include "ImageFormat.h"
#include <vector>
class PBMFormat:public ImageFormat
{
public:
	PBMFormat(int width = 0, int height = 0);
	
private:
	std::vector<std::vector<int>> matrix;
};

