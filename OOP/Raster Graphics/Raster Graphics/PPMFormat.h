#pragma once
#include "ImageFormat.h"
#include <vector>
class PPMFormat:public ImageFormat
{
public:
	PPMFormat(int width = 0, int height = 0, int maxValue = 0);

private:
	int maxValue;
	std::vector<std::vector<int[3]>> matrix;
};

