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
	pPixels = nullptr;
}

void Surface::PutPixel(const int x, const int y, const Color& c)
{
	pPixels[x + width * y] = c;
}

int Surface::Width() const
{
	return width;
}

int Surface::Height() const
{
	return height;
}

Color Surface::GetPixel(const int x, const int y) const
{
	return pPixels[x + width * y];
}
