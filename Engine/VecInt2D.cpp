#include "VecInt2D.h"

VecInt2D::VecInt2D(int x, int y)
    :
    x(x), 
    y(y)
{
}

VecInt2D& VecInt2D::operator+(const VecInt2D& v)
{
    VecInt2D result = { x + v.x, y + v.y };
    return result;
}

VecInt2D& VecInt2D::operator-(const VecInt2D& v)
{
    VecInt2D result = { x - v.x, y - v.y };
    return result;
}

VecInt2D& VecInt2D::operator*(const VecInt2D& v)
{
    VecInt2D result = { x * v.x, y * v.y };
    return result;
}

VecInt2D& VecInt2D::operator+=(const VecInt2D & v)
{
    x += v.x;
    y += v.y;
    return *this;
}

VecInt2D& VecInt2D::operator-=(const VecInt2D & v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

VecInt2D& VecInt2D::operator*=(const VecInt2D& v)
{
    x *= v.x;
    y *= v.y;
    return *this;
}

VecInt2D& VecInt2D::operator*(const int& n)
{
    VecInt2D result = { x * n, y * n };
    return result;
}

VecInt2D& VecInt2D::operator/(const int& n)
{
    VecInt2D result = { x / n, y / n };
    return result;
}

VecInt2D& VecInt2D::operator*=(const int& n)
{
    x *= n;
    y *= n;
    return *this;
}

VecInt2D& VecInt2D::operator/=(const int& n)
{
    x /= n;
    y /= n;
    return *this;
}

bool VecInt2D::operator==(const VecInt2D& v)
{
    return x == v.x && y == v.y;
}
