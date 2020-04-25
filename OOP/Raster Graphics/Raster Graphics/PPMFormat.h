#pragma once
#include "ImageFormat.h"
#include <vector>
#include <fstream>

class PPMFormat:public ImageFormat
{
public:
	PPMFormat(int width = 0, int height = 0, int maxValue = 0);

	void serialize(std::ofstream& out) const;

private:
	int maxValue;
	std::vector<std::vector<int[3]>> matrix;
};

