#include "Image.h"

ImageFormat::ImageFormat(int width, int height) :
	width(width),
	height(height)
{
}

ImageFormat::ImageFormat(std::ifstream& in)
{
	in.read((char*)&formatText, 2);
	in.read((char*)&width, sizeof(width));
	in.read((char*)&height, sizeof(height));

}

void ImageFormat::serialize(std::ofstream& out) const
{
	out.write((const char*)&formatText, 2);
	out.write((const char*)&width, sizeof(width));
	out.write((const char*)&height, sizeof(height));

}
