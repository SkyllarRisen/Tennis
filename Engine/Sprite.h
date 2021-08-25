#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "VecInt2D.h"
#include <vector>
#include <random>


class Sprite
{
public:

    Sprite(const std::vector<std::vector<Color>>& pixels, const VecInt2D pos, const VecInt2D vel, const VecInt2D maxVel, const bool fReflect);
    
    int X1() const;
    int X2() const;
    int Y1() const;
    int Y2() const;
    int VX() const;
    int VY() const;
    bool isColliding(const Sprite& obj);
    std::vector<std::vector<Color>> getSprite() const;


    void Draw(Graphics& gfx) const;
    void Update();
    void Control(const Keyboard& kbd, const char up, const char down, const char left, const char right);
    void Spawn(const bool winner = false);
    void InvertVX();
    void InvertVY();

    

public:

    bool hasCollidedX, hasCollidedY;
    //test
private:

    void BorderClamping();
    void BorderReflect();
    void BorderStop();
    bool hitBorderX() const;
    bool hitBorderY() const;
    void VelXChange(const int i);
    void VelYChange(const int i);
    int MaxVelX() const;
    int MaxVelY() const;

    std::vector<std::vector<Color>> pixels;
    VecInt2D pos, dim, vel, maxVel;
    const bool fReflect;

};

namespace Sprites
{
    static const std::vector<std::vector<Color>> wBall =    {
                                                            {Colors::Black, Colors::Black, Colors::White, Colors::White, Colors::White, Colors::White, Colors::Black, Colors::Black},
                                                            {Colors::Black, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::Black},
                                                            {Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White},
                                                            {Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White},
                                                            {Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White},
                                                            {Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White},
                                                            {Colors::Black, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::White, Colors::Black},
                                                            {Colors::Black, Colors::Black, Colors::White, Colors::White, Colors::White, Colors::White, Colors::Black, Colors::Black}
                                                            };

    static const std::vector<std::vector<Color>> wBar = std::vector<std::vector<Color>>(160, std::vector<Color>(16, Colors::White));

}

