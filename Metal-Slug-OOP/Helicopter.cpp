#include "Helicopter.h"
#include <raylib.h>
#include <time.h>
#include <cstdlib>

Helicopter::Helicopter()
{
    x = 1100;
    y = 130;
    EHealth = 100.0f;
    EHeight = 150;
    EWidth = 100;
    timer = 0;
    bulletFrame = 0;
    bulletsActive = 0;
    ECollider = { (float)x, (float)y, (float)EWidth, (float)EHeight };
}

void Helicopter::LoadImage()
{
    EImage = LoadTexture("Heli.png");
    EHeight = 150;
    EWidth = 100;
}

void Helicopter::Move()
{
    x -= 3;
    UpdateCollider();
}

void Helicopter::Shoot(Bullet bullets[])
{
    static int shootTimer = 0;
    if (x < 950)
    {
        shootTimer++;
        if (shootTimer >= 40)
        {
            for (int i = 0; i < 3; i++)
            {
                if (!bullets[i].GetActive())
                {
                    bullets[i].SetActive(true);
                    bullets[i].SetX(x + EWidth / 2);
                    bullets[i].SetY(y + 60);
                    bullets[i].SetVelX(0);
                    bullets[i].SetVelY(10);
                    break;
                }
            }
            shootTimer = 0;
        }
    }
    else
    {
        shootTimer = 0;
    }
}

void Helicopter::Draw()
{
    DrawTexture(EImage, x, y, WHITE);
}

void Helicopter::Respawn()
{
    x = 1100;
    y = 130;
    EHealth = 100.0f;
    UpdateCollider();
}

void Helicopter::HandleBullets(Bullet bullets[])
{
    for (int i = 0; i < 3; i++)
    {
        if (bullets[i].GetActive())
        {
            bullets[i].SetY(bullets[i].GetY() + 10);

            Rectangle collider;
            collider.x = (float)bullets[i].GetX();
            collider.y = (float)bullets[i].GetY();
            collider.width = (float)bullets[i].GetWidth();
            collider.height = (float)bullets[i].GetHeight();

            bullets[i].SetCollider(collider);
            if (bullets[i].GetY()> 600 - 50)
            {
                bullets[i].SetActive(false);
            }
            else 
            {
                bullets[i].Draw();
            }
        }
    }
}