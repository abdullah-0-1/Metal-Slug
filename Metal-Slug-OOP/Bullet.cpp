#include "Bullet.h"
#include <raylib.h>

Bullet::Bullet()
{
    x = 0;
    y = 0;
    BHeight = 10;
    BWidth = 20;
    active = false;
    vel_x = 0;
    vel_y = 0;
    BImage = { 0 };
    BCollider = { 0, 0, (float)BWidth, (float)BHeight };
}

void Bullet::Load(const char* Fname, int px, int py)
{
    BImage = LoadTexture(Fname);
    x = px;
    y = py;
    BHeight = 10;
    BWidth = 20;
    active = false;
    vel_x = 0;
    vel_y = 0;
    BCollider = { (float)x, (float)y, (float)BWidth, (float)BHeight };
}

void Bullet::Move()
{
    x += vel_x;
    y += vel_y;
    BCollider.x = (float)x;
    BCollider.y = (float)y;
}

void Bullet::Draw()
{
    if (active)
    {
        DrawTexture(BImage, x, y, WHITE);
    }
}

void Bullet::Reset()
{
    active = false;
    x = 0;
    y = 0;
    vel_x = 0;
    vel_y = 0;
    BCollider = { (float)x, (float)y, (float)BWidth, (float)BHeight };
}

// Getters
int Bullet::GetX() const
{
    return x;
}

int Bullet::GetY() const
{
    return y;
}

Texture2D Bullet::GetImage() const
{
    return BImage;
}

bool Bullet::GetActive() const
{
    return active;
}

int Bullet::GetHeight() const
{
    return BHeight;
}

int Bullet::GetWidth() const
{
    return BWidth;
}

Rectangle Bullet::GetCollider() const
{
    return BCollider;
}

int Bullet::GetVelX() const
{
    return vel_x;
}

int Bullet::GetVelY() const
{
    return vel_y;
}

// Setters
void Bullet::SetX(int val)
{
    x = val;
}

void Bullet::SetY(int val)
{
    y = val;
}

void Bullet::SetImage(Texture2D img)
{
    BImage = img;
}

void Bullet::SetActive(bool val)
{
    active = val;
}

void Bullet::SetHeight(int val)
{
    BHeight = val;
}

void Bullet::SetWidth(int val)
{
    BWidth = val;
}

void Bullet::SetCollider(const Rectangle& rect)
{
    BCollider = rect;
}

void Bullet::SetVelX(int val)
{
    vel_x = val;
}

void Bullet::SetVelY(int val)
{
    vel_y = val;
}