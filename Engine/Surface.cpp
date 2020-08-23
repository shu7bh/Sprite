#include "Surface.h"

Surface::Surface(const int width, const int height)
	: width(width), height(height), pPixels(new Color[size_t(width) * height]) {}

Surface::Surface(const Surface& rhs)
	: Surface(rhs.width, rhs.height)
{
	for (int i = 0; i < width * height; ++i)
		pPixels[i] = rhs.pPixels[i];
}

Surface& Surface::operator=(const Surface& rhs)
{
	delete[] pPixels;
	width = rhs.width, height = rhs.height;
	pPixels = new Color[size_t(width) * height];

	for (int i = 0; i < width * height; ++i)
		pPixels[i] = rhs.pPixels[i];

	return *this;
}

Surface::~Surface()
{
	delete[] pPixels;
}

int Surface::Width() const
{
	return width;
}

int Surface::Height() const
{
	return height;
}

Color* Surface::PPixels()
{
	return pPixels;
}
