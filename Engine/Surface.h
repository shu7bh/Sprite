#pragma once
#include "Colors.h"

class Surface
{
public:
	// Constructors
	Surface(const int width, const int height);
	Surface(const Surface& rhs);

	// Assignment operator
	Surface& operator=(const Surface& rhs);

	// Destructor
	~Surface();

	// Modifier
	void PutPixel(const int x, const int y, const Color& c);

	// Getters
	int Width() const;
	int Height() const;
	Color GetPixel(const int x, const int y) const;
private:
	int width;
	int height;
	Color* pPixels = nullptr;
};

