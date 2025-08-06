#include "EnemyParent.h"

EnemyParent::EnemyParent()
{
    x = 0;
    y = 0;
    EHealth = 100.0f;
    EHeight = 0;
    EWidth = 0;
    timer = 0;
    bulletFrame = 0;
    bulletsActive = 0;
    ECollider = { 0, 0, 0, 0 };
}

void EnemyParent::TakeDamage(float dmg)
{
    EHealth -= dmg;
    if (EHealth < 0)
    {
        EHealth = 0;
    }
}

void EnemyParent::UpdateCollider()
{
    ECollider.x = (float)x;
    ECollider.y = (float)y;
    ECollider.width = (float)EWidth;
    ECollider.height = (float)EHeight;
}

// Getters
int EnemyParent::GetX() const
{
    return x;
}

int EnemyParent::GetY() const
{
    return y;
}

Rectangle EnemyParent::GetCollider() const
{
    return ECollider;
}

float EnemyParent::GetHealth() const
{
    return EHealth;
}

Texture2D EnemyParent::GetImage() const
{
    return EImage;
}

int EnemyParent::GetHeight() const
{
    return EHeight;
}

int EnemyParent::GetWidth() const
{
    return EWidth;
}

int EnemyParent::GetTimer() const
{
    return timer;
}

int EnemyParent::GetBulletFrame() const
{
    return bulletFrame;
}

int EnemyParent::GetBulletsActive() const
{
    return bulletsActive;
}

// Setters
void EnemyParent::SetX(int val)
{
    x = val;
}

void EnemyParent::SetY(int val)
{
    y = val;
}

void EnemyParent::SetCollider(const Rectangle& rect)
{
    ECollider = rect;
}

void EnemyParent::SetHealth(float val)
{
    EHealth = val;
}

void EnemyParent::SetImage(Texture2D img)
{
    EImage = img;
}

void EnemyParent::SetHeight(int val)
{
    EHeight = val;
}

void EnemyParent::SetWidth(int val)
{
    EWidth = val;
}

void EnemyParent::SetTimer(int val)
{
    timer = val;
}

void EnemyParent::SetBulletFrame(int val)
{
    bulletFrame = val;
}

void EnemyParent::SetBulletsActive(int val)
{
    bulletsActive = val;
}