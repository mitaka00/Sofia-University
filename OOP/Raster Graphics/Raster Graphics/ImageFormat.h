#pragma once
class ImageFormat
{
public:
	ImageFormat(int width=0,int height=0);
	ImageFormat(std::ifstream& in);
	
	void serialize(std::ofstream& out) const;

protected:
	int width;
	int height;
	std::string formatText;
};

