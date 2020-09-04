#include <wtypes.h>
#include <vector>
#include "Circle.h"


CircleShape::CircleShape(const Point& _center, int _radius, horDirections _hor, verDirections _ver, COLORREF _colorBrush
    , COLORREF _colorPen)
    :center(_center), radius(_radius), hor(_hor), ver(_ver), speedX(4), speedY(4), colorBrush(_colorBrush), 
    colorPen(_colorPen), weight(pow(_radius, 2))
{}

CircleShape::~CircleShape() {}

void CircleShape::Draw(HDC& hdc)const
{
    //Перо и кисть
    HBRUSH shapeBrush = CreateSolidBrush(colorBrush);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, shapeBrush);
    HPEN shapePen = CreatePen(PS_SOLID, 3, colorPen);
    HPEN oldPen = (HPEN)SelectObject(hdc, shapePen);

    //Рисование
    Ellipse(hdc, center.x - radius, center.y - radius,
        center.x + radius, center.y + radius);

    //Перо и кисть
    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(shapeBrush);
    DeleteObject(shapePen);
}



void CircleShape::WithBorder(int x, int y, int width, int height)
{
    width += x;
    height += y;
    if (center.x + radius >= width)
    {
        center.x = width - radius;
        speedX *= -1;
    }
    if (center.x - radius <= x)
    {
        center.x = radius + x;
        speedX *= -1;
    }

    if (center.y - radius <= y)
    {
        center.y = radius + y;
        speedY *= -1;
    }
    if (center.y + radius >= height)
    {
        center.y = height - radius;
        speedY *= -1;
    }
}

void CircleShape::WithBorderRedact(int x, int y, int width, int height)
{
    width += x;
    height += y;
    if (center.x + radius >= width)
    {
        center.x = width - radius;
    }
    if (center.x - radius <= x)
    {
        center.x = radius + x;
    }

    if (center.y - radius <= y)
    {
        center.y = radius + y;
    }
    if (center.y + radius >= height)
    {
        center.y = height - radius;
    }
}

void CircleShape::Move()
{
    center.x += speedX;
    center.y += speedY;
}

////////////////////////////////
    //////// Get

int CircleShape::GetX()
{
    return center.x;
}

int CircleShape::GetY()
{
    return center.y;
}

int CircleShape::GetRadius()
{
    return radius;
}

int CircleShape::GetWeight()
{
    return weight;
}

double CircleShape::GetSpeedX()
{
    return speedX;
}

double CircleShape::GetSpeedY()
{
    return speedY;
}

////////////////////////////////
//////// Set

void CircleShape::SetX(int _x)
{
    center.x = _x;
}

void CircleShape::SetY(int _y)
{
    center.y = _y;
}

void CircleShape::SetRadius(int _r)
{
    radius = _r;
}

void CircleShape::SetWeight(int _m)
{
    weight = _m;
}

void CircleShape::SetSpeedX(double _s)
{
    speedX = _s;
}

void CircleShape::SetSpeedY(double _s)
{
    speedY = _s;
}

void CircleShape::SetColorBrush(COLORREF _colorBrush)
{
    colorBrush = _colorBrush;
}