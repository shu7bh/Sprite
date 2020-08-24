#include "Surface.h"
#include <cassert>
#include <fstream>
#include "Graphics.h"
#include "ChiliException.h"

Surface::Surface(const int width, const int height)
	: width(width), height(height), pPixels(new Color[size_t(width) * height]) {}

Surface::Surface(const Surface& rhs)
	: Surface(rhs.width, rhs.height)
{
	for (int i = 0; i < width * height; ++i)
		pPixels[i] = rhs.pPixels[i];
}

Surface::Surface(const std::wstring fileName)
{
	std::ifstream fin(fileName, std::ios::binary);
	assert(fin);

	BITMAPFILEHEADER bmFileHeader;
	fin.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	fin.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB);
	assert(bmInfoHeader.biWidth < Graphics::ScreenWidth);
	assert(bmInfoHeader.biHeight < Graphics::ScreenHeight);

	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;

	pPixels = new Color[width * abs(height)];
	
	fin.seekg(bmFileHeader.bfOffBits);
	 
	const int padding = (4 - (width * 3) % 4) % 4;

	if (height >= 0)
		for (int j = height - 1; j >= 0; --j)
		{
			for (int i = 0; i < width; ++i)
			{
				if (bmInfoHeader.biBitCount == 32)
					fin.get();
				PutPixel(i, j, Color(fin.get(), fin.get(), fin.get()));
			}
			fin.seekg(padding, std::ios::cur);
		}
	else
	{
		height = -height;
		for (int j = 0; j < height; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				if (bmInfoHeader.biBitCount == 32)
					fin.get();
				PutPixel(i, j, Color(fin.get(), fin.get(), fin.get()));
			}
			fin.seekg(padding, std::ios::cur);
		}
	}
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
	assert(x >= 0);
	assert(y >= 0);
	assert(x < width);
	assert(y < height);

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
	assert(x >= 0);
	assert(y >= 0);
	assert(x < width);
	assert(y < height);

	return pPixels[x + width * y];
}
