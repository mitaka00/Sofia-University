#include "PGMFormat.h"

PGMFormat::PGMFormat(int width, int height, int maxValue):
	ImageFormat(width,height),
	maxValue(maxValue)
{
}
