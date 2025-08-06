#include "Shield.h"
#include "Player.h"
#include <raylib.h>

Shield::Shield()
{
    health = 100.0f;
    active = false;
    SImage = { 0 };
}

void Shield::Draw(Player& P)
{
    if (active && health > 0)
    {
        DrawTexture(SImage,P.GetX(0)+ 25,P.GetY(0)- 10, WHITE);
    }
}

void Shield::Update()
{
    if (health <= 0)
    {
        active = false;
    }
}

// Getters
float Shield::GetHealth() const
{
    return health;
}

Texture2D Shield::GetImage() const
{
    return SImage;
}

bool Shield::GetActive() const
{
    return active;
}

// Setters
void Shield::SetHealth(float val)
{
    health = val;
}

void Shield::SetImage(Texture2D img)
{
    SImage = img;
}

void Shield::SetActive(bool val)
{
    active = val;
}