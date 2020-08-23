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

	// Getters
	int Width() const;
	int Height() const;
	Color* PPixels();
private:
	int width;
	int height;
	Color* pPixels = nullptr;
};

