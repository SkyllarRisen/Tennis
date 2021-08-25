#pragma once

struct VecInt2D
{
    int x;
    int y;

    VecInt2D(int x, int y);

    VecInt2D& operator + (const VecInt2D& v);
    VecInt2D& operator - (const VecInt2D& v);
    VecInt2D& operator * (const VecInt2D& v);
    VecInt2D& operator += (const VecInt2D& v);
    VecInt2D& operator -= (const VecInt2D& v);
    VecInt2D& operator *= (const VecInt2D& v);

    VecInt2D& operator * (const int& n);
    VecInt2D& operator / (const int& n);
    VecInt2D& operator *= (const int& n);
    VecInt2D& operator /= (const int& n);

    bool operator == (const VecInt2D& v);

};