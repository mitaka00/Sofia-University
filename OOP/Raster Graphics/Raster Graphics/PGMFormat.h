#pragma once
#include "ImageFormat.h"
#include <vector>
class PGMFormat:public ImageFormat
{
public:
	PGMFormat(int width = 0, int height = 0, int maxValue = 0);
private:
	int maxValue;
	std::vector<std::vector<int>> matrix;
};

