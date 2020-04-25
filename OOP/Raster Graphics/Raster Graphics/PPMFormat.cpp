#include "PPMFormat.h"

PPMFormat::PPMFormat(int width, int height, int maxValue):
	ImageFormat(width, height),
	maxValue(maxValue)
{
}

void PPMFormat::serialize(std::ofstream& out) const
{
	ImageFormat::serialize(out);
	//todo
}
