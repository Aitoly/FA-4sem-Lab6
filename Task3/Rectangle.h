#pragma once

#include "Point.h"

class RectangleShape
{
public:
	RectangleShape(const Point&, const Point&);
	~RectangleShape();
	void Draw(HDC& hdc) const;

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	void SetWH(const Point&);

private:
	Point upLeftPiont, widthAndHeight;
};

