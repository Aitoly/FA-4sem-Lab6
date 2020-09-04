#pragma warning(disable:4996)

#include <wtypes.h>
#include <vector>
#include "Circle.h"

#include "VectorOfShapes.h"

VectorOfShapes::VectorOfShapes() : click(false), focusShape(nullptr)
{}

VectorOfShapes::~VectorOfShapes() 
{
    for (int i = 0; i < shapes.size(); ++i)
    {
        delete shapes[i];
    }
}

double VectorOfShapes::conservationOfMomentum(int m1, int m2, double speed1, double speed2)
{
    return ((2 * m2 * speed2 + (m1 - m2) * speed1) / (m1 + m2));
}

bool VectorOfShapes::Load() 
{
    shapes.clear();

    FILE* f;
    f = fopen("save.txt", "r");

    if (!f)
    {
        return false;
    }

    int count = 0;
    fscanf_s(f, "%d", &count);

    for (int i = 0; i < count; ++i)
    {
        int x, y, r;
        fscanf_s(f, "\n%d %d %d", &x, &y, &r);
        shapes.push_back(new CircleShape(Point(x, y), r, CircleShape::horDirections::right, CircleShape::verDirections::down,
            RGB(128, 255, 0), RGB(128, 255, 0)));
    }
    fclose(f);
    return true;
}

bool VectorOfShapes::Save()
{
    FILE* f;
    f = fopen("save.txt", "w");

    if (!f)
    {
        return false;
    }

    int count = shapes.size();
    fprintf_s(f, "%d\n", count);

    for (int i = 0; i < count; ++i)
    {
        fprintf_s(f, "%d %d %d\n", shapes[i]->GetX(), shapes[i]->GetY(), shapes[i]->GetRadius());
    }
    fclose(f);
    return true;
}

void VectorOfShapes::Boom(int i)
{
    for (int j = i + 1; j < shapes.size(); ++j)
    {
        int sumRadius = shapes[i]->GetRadius() + shapes[j]->GetRadius();
        int distCenters = (int)sqrt(pow(shapes[i]->GetX() - shapes[j]->GetX(), 2) + pow(shapes[i]->GetY() - shapes[j]->GetY(), 2));


        if (distCenters < sumRadius)
        {
            int lenX = (shapes[j]->GetX() - shapes[i]->GetX()) * sumRadius / distCenters;
            int lenY = (shapes[j]->GetY() - shapes[i]->GetY()) * sumRadius / distCenters;

            shapes[i]->SetX(shapes[j]->GetX() - lenX);
            shapes[i]->SetY(shapes[j]->GetY() - lenY);

            double NewSpeedX_I = conservationOfMomentum(shapes[i]->GetWeight(), shapes[j]->GetWeight(), shapes[i]->GetSpeedX(), shapes[j]->GetSpeedX());
            double NewSpeedY_I = conservationOfMomentum(shapes[i]->GetWeight(), shapes[j]->GetWeight(), shapes[i]->GetSpeedY(), shapes[j]->GetSpeedY());

            double NewSpeedX_J = conservationOfMomentum(shapes[j]->GetWeight(), shapes[i]->GetWeight(), shapes[j]->GetSpeedX(), shapes[i]->GetSpeedX());
            double NewSpeedY_J = conservationOfMomentum(shapes[j]->GetWeight(), shapes[i]->GetWeight(), shapes[j]->GetSpeedY(), shapes[i]->GetSpeedY());

            shapes[i]->SetSpeedX(NewSpeedX_I);
            shapes[i]->SetSpeedY(NewSpeedY_I);

            shapes[j]->SetSpeedX(NewSpeedX_J);
            shapes[j]->SetSpeedY(NewSpeedY_J);
        }
    }
}

void VectorOfShapes::Update(int x, int y, int width, int height)
{
    for (int i = 0; i < shapes.size(); ++i)
    {
        if (click)
        {
            if (shapes[i] != focusShape)
            {
                /*shapes[i]->Move();
                shapes[i]->WithBorder(x, y, width, height);
                Boom(i);*/
            }
            else
            {
                shapes[i]->WithBorderRedact(x, y, width, height);
                //Boom(i);
            }
        }
        else
        {
            shapes[i]->Move();
            shapes[i]->WithBorder(x, y, width, height);
            Boom(i);
        }
    }
}

void VectorOfShapes::Draw(HDC &hdc)
{
    for (int i = 0; i < shapes.size(); ++i)
    {
        shapes[i]->Draw(hdc);
    }
}

void VectorOfShapes::lButtonDown(int x, int y)
{
    if (!click)
    {
        int size = shapes.size();
        for (int i = size - 1; i >= 0; --i)
        {
            int distCenterAndMouse = (int)sqrt(pow(shapes[i]->GetX() - x, 2) + pow(shapes[i]->GetY() - y, 2));
            if (distCenterAndMouse < shapes[i]->GetRadius())
            {
                focusShape = shapes[i];
                click = true;
                return;
            }
        }
    }
}

void VectorOfShapes::mouseMove(int x, int y)
{
    if (click && focusShape != nullptr)
    {
        focusShape->SetX(x);
        focusShape->SetY(y);
    }
}

void VectorOfShapes::lButtonUp()
{
    if (click)
    {
        click = false;
        focusShape = nullptr;
    }
}

CircleShape* VectorOfShapes::dblClick(int x, int y)
{
    int size = shapes.size();
    for (int i = size - 1; i >= 0; --i)
    {
        int distCenterAndMouse = (int)sqrt(pow(shapes[i]->GetX() - x, 2) + pow(shapes[i]->GetY() - y, 2));
        if (distCenterAndMouse < shapes[i]->GetRadius())
        {
            return shapes[i];
        }
    }

    return nullptr;
}

void VectorOfShapes::SettingsShape(CircleShape* shape, int x, int y, int r, int w)
{
    if (shape)
    {
        shape->SetX(x);
        shape->SetY(y);
        if(r > 0 && r < 101)
            shape->SetRadius(r);
        if(w > 0 && w < 50001)
            shape->SetWeight(w);
    }
}
