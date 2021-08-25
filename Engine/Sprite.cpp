#include "Sprite.h"
#include "Graphics.h"
#include <assert.h>

Sprite::Sprite(const std::vector<std::vector<Color>>& pixels, const VecInt2D pos, const VecInt2D vel, const VecInt2D maxVel, const bool fReflect)
    : 
    pixels(pixels), 
    pos(pos),
    dim(pixels.at(0).size(), pixels.size()),
    vel(vel),
    maxVel(maxVel),
    fReflect(fReflect), 
    hasCollidedX(false), 
    hasCollidedY(false)
{
    for (int i = 0; i < pixels.size(); ++i)
    {
        assert(pixels.at(i).size() == dim.x);
    }
    
}

void Sprite::Draw(Graphics& gfx) const
{
    for (int j = 0; j < dim.y; ++j)
    {
        for (int i = 0; i < dim.x; ++i)
        {
            gfx.PutPixel(X1()+i, Y1()+j, pixels.at(j).at(i));
        }
    }
}

void Sprite::Update()
{
    BorderClamping();
    pos.x = X1() + VX();
    pos.y = Y1() + VY();
}

void Sprite::VelXChange(const int v_x_in)
{
    if (VX() + v_x_in <= MaxVelX() && VX() + v_x_in >= -MaxVelX())
        vel.x += v_x_in;
    else if (VX() + v_x_in > MaxVelX())
        vel.x = MaxVelX();
    else
        vel.x = -MaxVelX();
}

void Sprite::VelYChange(const int v_y_in)
{
    if (VY() + v_y_in <= MaxVelY() && VY() + v_y_in >= -MaxVelY())
        vel.y += v_y_in;
    else if (VY() + v_y_in > MaxVelY())
        vel.y = MaxVelY();
    else
        vel.y = -MaxVelY();
}

int Sprite::MaxVelX() const
{
    return maxVel.x;
}

int Sprite::MaxVelY() const
{
    return maxVel.y;
}

int Sprite::X1() const
{
    return pos.x;
}

int Sprite::X2() const
{
    return X1() + dim.x;
}

int Sprite::Y1() const
{
    return pos.y;
}

int Sprite::Y2() const
{
    return Y1() + dim.y;
}

int Sprite::VX() const
{
    return vel.x;
}

int Sprite::VY() const
{
    return vel.y;
}

bool Sprite::isColliding(const Sprite &obj)
{    
    return (X1() + VX() < obj.X2() && X2() + VX() >= obj.X1() && Y1() + VY() < obj.Y2() && Y2() + VY() >= obj.Y1());
}

std::vector<std::vector<Color>> Sprite::getSprite() const
{
    return pixels;
}

void Sprite::Spawn(const bool winner)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrPos(Graphics::ScreenHeight / 4, Graphics::ScreenHeight * 3 / 4);
    std::uniform_int_distribution<int> distrVel(0,1);
    
    pos.x = Graphics::ScreenWidth/2 - 3;
    pos.y = distrPos(gen);
    if (!distrVel(gen))
        vel.y = -VY();
    if (!winner)
    {
        if (!distrVel(gen))
            vel.x = -VX();
    }
    else
    {

    }
}

void Sprite::InvertVX()
{
    vel.x = -VX();
}

void Sprite::InvertVY()
{
    vel.y = -VY();
}

void Sprite::Control(const Keyboard& kbd, const char up, const char down, const char left, const char right)
{
    if (kbd.KeyIsPressed(up))
        VelYChange(-1);
    if (kbd.KeyIsPressed(down))
        VelYChange(+1);
    if (!(kbd.KeyIsPressed(up) || kbd.KeyIsPressed(down)))
        vel.y = 0;
}

void Sprite::BorderClamping()
{
    if (fReflect)
        BorderReflect();
    else
        BorderStop();
}

void Sprite::BorderReflect()
{
    if (hitBorderX())
    {
        if (pos.x + VX() < 0)
            pos.x = -X1();
        else
            pos.x = Graphics::ScreenWidth - 1 - dim.x + (Graphics::ScreenWidth - 1 - X2());
        InvertVX();
    }
    if (hitBorderY())
    {
        if (Y1() + VY() < 0)
            pos.y = -Y1();
        else
            pos.y = Graphics::ScreenHeight - 1 - dim.y + (Graphics::ScreenHeight - 1 - Y2());
        InvertVY();
    }
}

void Sprite::BorderStop()
{
    if (hitBorderX())
    {
        if (X1() + VX() < 0)
            pos.x = 0;
        else
            pos.x = Graphics::ScreenWidth - 1 - dim.x;
        vel.x = 0;
        vel.y = 0;
    }
    if (hitBorderY())
    {
        if (Y1() + VY() < 0)
            pos.y = 0;
        else
            pos.y = Graphics::ScreenHeight - 1 - dim.y;
        vel.x = 0;
        vel.y = 0;
    }
}

bool Sprite::hitBorderX() const
{
    return X1() + VX() < 0 || X2() + VX() >= Graphics::ScreenWidth;
}
bool Sprite::hitBorderY() const
{
    return Y1() + VY() < 0 || Y2() + VY() >= Graphics::ScreenHeight;
}



