#pragma once

#include "Point.h"

class CircleShape
{
public:

	enum class horDirections
	{
		left, right
	};

	enum class verDirections
	{
		up, down
	};

	CircleShape(const Point&, int, horDirections, verDirections, COLORREF, COLORREF);
	~CircleShape();

	void Draw(HDC& hdc) const;

	void WithBorder(int, int, int, int);
	void WithBorderRedact(int, int, int, int);
	void Move();
	

	////////////////////////////////
	//////// Get

	int GetX();
	int GetY();
	int GetRadius();
	int GetWeight();
	double GetSpeedX();
	double GetSpeedY();

	////////////////////////////////
	//////// Set

	void SetX(int);
	void SetY(int);
	void SetRadius(int);
	void SetWeight(int);
	void SetSpeedX(double);
	void SetSpeedY(double);
	void SetColorBrush(COLORREF);

private:
	Point center;
	int radius;
	int weight;

	horDirections hor;
	verDirections ver;
	double speedX, speedY;
	COLORREF colorBrush;
	COLORREF colorPen;
};

