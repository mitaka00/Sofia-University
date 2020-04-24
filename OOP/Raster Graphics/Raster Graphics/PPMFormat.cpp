#include "PPMFormat.h"

PPMFormat::PPMFormat(int width, int height, int maxValue):
	ImageFormat(width, height),
	maxValue(maxValue)
{
}
