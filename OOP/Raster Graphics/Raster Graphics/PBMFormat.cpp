#include "PBMFormat.h"

PBMFormat::PBMFormat(int width, int height):
	ImageFormat(width,height)
{
}

void PBMFormat::serialize(std::ofstream& out) const
{
	ImageFormat::serialize(out);
	//todo
}
