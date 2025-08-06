#include "Enemy.h"
#include <raylib.h>

Enemy::Enemy()
{
    x = 800;
    y = 430;
    EHealth = 100.0f;
    EHeight = 150;
    EWidth = 100;
    timer = 0;
    bulletFrame = 0;
    bulletsActive = 0;
    ECollider = { (float)x, (float)y, (float)EWidth, (float)EHeight };
}

void Enemy::LoadImage()
{
    EImage = LoadTexture("Enemy.png");
    EHeight = 150;
    EWidth = 100;
}

void Enemy::Move()
{
    x -= 1;
    UpdateCollider();
}

void Enemy::Shoot(Bullet bullets[])
{
    for (int i = 0; i < 3; i++)
    {
        if (!bullets[i].GetActive())
        {
            bullets[i].SetActive(true);
            bullets[i].SetX(x);
            bullets[i].SetY(y + 40);
            bullets[i].SetVelX(-5);
            bullets[i].SetVelY(0);
            break;
        }
    }
}

void Enemy::Draw()
{
    DrawTexture(EImage, x, y, WHITE);
}

void Enemy::Respawn()
{
    x = 1000;
    y = 600 - EHeight + 25;
    EHealth = 100.0f;
    UpdateCollider();
}
void Enemy::HandleBullets(Bullet bullets[])
{
    for (int i = 0; i < 3; i++)
    {
        if (bullets[i].GetActive())
        {
            bullets[i].SetX(bullets[i].GetX()-5);
            Rectangle collider;
            collider.x = (float)bullets[i].GetX();
            collider.y = (float)bullets[i].GetY();
            collider.width = (float)bullets[i].GetWidth();
            collider.height = (float)bullets[i].GetHeight();

            bullets[i].SetCollider(collider);

            if (bullets[i].GetX()< 0) 
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