#include "EnemyMan.h"
#include <raylib.h>

EnemyMan::EnemyMan()
{
    x = 900;
    y = 430;
    EHealth = 100.0f;
    EHeight = 150;
    EWidth = 100;
    timer = 0;
    bulletFrame = 0;
    bulletsActive = 0;
    ECollider = { (float)x, (float)y, (float)EWidth, (float)EHeight };
}

void EnemyMan::LoadImage()
{
    EImage = LoadTexture("Enemy_Man.png");
    EHeight = 150;
    EWidth = 100;
}

void EnemyMan::Move()
{
    x -= 2;
    UpdateCollider();
}

void EnemyMan::Shoot(Bullet bullets[])
{
    for (int i = 0; i < 3; i++)
    {
        if (!bullets[i].GetActive())
        {
            bullets[i].SetActive(true);
            bullets[i].SetX(x);
            bullets[i].SetY(y + 40);
            bullets[i].SetVelX(-6);
            bullets[i].SetVelY(0);
            break;
        }
    }
}

void EnemyMan::Draw()
{
    DrawTexture(EImage, x, y, WHITE);
}

void EnemyMan::Respawn()
{
    x = 1000;
    y = 600 - EHeight + 25;
    EHealth = 100.0f;
    UpdateCollider();
}

void EnemyMan::HandleBullets(Bullet bullets[])
{
    for (int i = 0; i < 3; i++)
    {
        if (bullets[i].GetActive())
        {
            bullets[i].SetX(bullets[i].GetX() - 6);

            Rectangle collider;
            collider.x = (float)bullets[i].GetX();
            collider.y = (float)bullets[i].GetY();
            collider.width = (float)bullets[i].GetWidth();
            collider.height = (float)bullets[i].GetHeight();

            bullets[i].SetCollider(collider);
            if (bullets[i].GetX() < 0)
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