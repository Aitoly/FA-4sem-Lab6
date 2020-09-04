#include <wtypes.h>
#include "Rectangle.h"

RectangleShape::RectangleShape(const Point& _upLeftPiont, const Point& _widthAndHeight)
    :upLeftPiont(_upLeftPiont), widthAndHeight(_widthAndHeight)
{}

RectangleShape::~RectangleShape() {}

void RectangleShape::Draw(HDC& hdc)const
{
    //Перо и кисть
    HPEN shapePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN oldPen = (HPEN)SelectObject(hdc, shapePen);

    //Рисование
    Rectangle(hdc, upLeftPiont.x, upLeftPiont.y,
        upLeftPiont.x + widthAndHeight.x, upLeftPiont.y + widthAndHeight.y);

    //Перо и кисть
    SelectObject(hdc, oldPen);
    DeleteObject(shapePen);
}

int RectangleShape::GetX()
{
    return upLeftPiont.x;
}

int RectangleShape::GetY()
{
    return upLeftPiont.y;
}
int RectangleShape::GetWidth()
{
    return widthAndHeight.x;
}
int RectangleShape::GetHeight()
{
    return widthAndHeight.y;
}

void RectangleShape::SetWH(const Point& p)
{
    widthAndHeight.x = p.x;
    widthAndHeight.y = p.y;
}
