#include "PGMFormat.h"

PGMFormat::PGMFormat(int width, int height, int maxValue):
	ImageFormat(width,height),
	maxValue(maxValue)
{
}

void PGMFormat::serialize(std::ofstream& out) const
{
	ImageFormat::serialize(out);
	//todo
}
