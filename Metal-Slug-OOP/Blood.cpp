#include "Blood.h"
#include <raylib.h>

Blood::Blood()
{
    x = 0;
    y = 0;
    BHeight = 80;
    BWidth = 100;
    BloodFrame = 0;
    IsBlood = false;
    BloodTime = 0;
}

void Blood::LoadImages()
{
    PBlood[0] = LoadTexture("Blood_1.png");
    PBlood[1] = LoadTexture("Blood_2.png");
    PBlood[2] = LoadTexture("Blood_3.png");
    PBlood[3] = LoadTexture("Blood_4.png");
}

void Blood::Show()
{
    if (IsBlood)
    {
        DrawTexture(PBlood[BloodFrame], x, y, WHITE);
        if (BloodTime > 0)
        {
            BloodTime--;
            if (BloodTime % 5 == 0)
            {
                BloodFrame++;
                if (BloodFrame >= 4)
                {
                    BloodFrame = 0;
                }
            }
        }
        else
        {
            IsBlood = false;
        }
    }
}

void Blood::Start(int px, int py)
{
    x = px;
    y = py;
    IsBlood = true;
    BloodFrame = 0;
    BloodTime = 30;
}

int Blood::GetX() const
{
    return x;
}

int Blood::GetY() const
{
    return y;
}

Texture2D Blood::GetBloodImage(int idx) const
{
    return PBlood[idx];
}

int Blood::GetHeight() const
{
    return BHeight;
}

int Blood::GetWidth() const
{
    return BWidth;
}

int Blood::GetBloodFrame() const
{
    return BloodFrame;
}

bool Blood::GetIsBlood() const
{
    return IsBlood;
}

int Blood::GetBloodTime() const
{
    return BloodTime;
}

// Setters
void Blood::SetX(int val)
{
    x = val;
}

void Blood::SetY(int val)
{
    y = val;
}

void Blood::SetBloodImage(int idx, Texture2D img)
{
    PBlood[idx] = img;
}

void Blood::SetHeight(int val)
{
    BHeight = val;
}

void Blood::SetWidth(int val)
{
    BWidth = val;
}

void Blood::SetBloodFrame(int val)
{
    BloodFrame = val;
}

void Blood::SetIsBlood(bool val)
{
    IsBlood = val;
}

void Blood::SetBloodTime(int val)
{
    BloodTime = val;
}