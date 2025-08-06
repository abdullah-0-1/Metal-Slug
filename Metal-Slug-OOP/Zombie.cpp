#include "Zombie.h"
#include <raylib.h>
#include <cstdlib>
#include <ctime>

Zombie::Zombie()
{
    x = 0;
    y = 0;
    EHealth = 100.0f;
    EHeight = 140;
    EWidth = 70;
    timer = 0;
    bulletFrame = 0;
    bulletsActive = 0;
    visible = false;
    ECollider = { (float)x, (float)y, (float)EWidth, (float)EHeight };
}

void Zombie::LoadImage()
{
    EImage = LoadTexture("Zombie.png");
    EHeight = 140;
    EWidth = 70;
}

void Zombie::Move()
{
    if (!visible) 
    {
        return;
    }
    x -= 4;
    UpdateCollider();
}

void Zombie::Draw()
{
    if (visible)
    {
        Color Tint = { 40, 40, 40, 255 };
        DrawTexture(EImage, x, y, Tint);
    }
}

void Zombie::RespawnNearPlayer(int playerX, int playerY)
{
    x = playerX + 250 + rand() % 100;
    y = 600 - EHeight+10;
    visible = false;
    UpdateCollider();
}

// Getter
bool Zombie::GetVisible() const
{
    return visible;
}

// Setter
void Zombie::SetVisible(bool val)
{
    visible = val;
}