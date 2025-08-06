#include "Boss.h"
#include "Player.h"
#include "Shield.h"
#include "Blood.h"
#include <raylib.h>

Boss::Boss()
{
    x = 0;
    y = 0;
    BossHealth = 200.0f;
    BossHeight = 220;
    BossWidth = 255;
    Bosstimer = 0;
    BossbulletFrame = 0;
    BossActive = false;
    BossDefeated = false;
    BossDefeatFrame = 0;
    BossDefeatTimer = 0;
    BossCollider = { (float)x, (float)y, (float)BossWidth, (float)BossHeight };
    for (int i = 0; i < 3; i++)
    {
        BossBullet[i].SetActive(false);
        BossBullet[i].SetX(0);
        BossBullet[i].SetY(0);
        BossBullet[i].SetVelX(0);
        BossBullet[i].SetVelY(0);
        BossBullet[i].SetHeight(10);
        BossBullet[i].SetWidth(20);
    }
}

void Boss::LoadImages()
{
    BossImage[0] = LoadTexture("Boss1.png");
    BossImage[1] = LoadTexture("Boss2.png");
    BossImage[2] = LoadTexture("Boss3.png");
    BossImage[3] = LoadTexture("Boss4.png");
    BossImage[4] = LoadTexture("Boss5.png");
    BossImage[5] = LoadTexture("Boss6.png");
    BossImage[6] = LoadTexture("Boss7.png");
    BossImage[7] = LoadTexture("Boss8.png");
    BossImage[8] = LoadTexture("Boss9.png");
    BossImage[9] = LoadTexture("Boss10.png");
    BossHeight = 220;
    BossWidth = 255;
    x = 1000 - BossWidth - 10;
    y = 600 - BossHeight + 10;

    BossDefeatImage[0] = LoadTexture("Boss11.png");
    BossDefeatImage[1] = LoadTexture("Boss12.png");
    BossDefeatImage[2] = LoadTexture("Boss13.png");
    BossDefeatImage[3] = LoadTexture("Boss14.png");
    BossDefeatImage[4] = LoadTexture("Boss15.png");
    BossDefeatImage[5] = LoadTexture("Boss16.png");
    BossDefeatImage[6] = LoadTexture("Boss17.png");
    BossDefeatImage[7] = LoadTexture("Boss18.png");
}

void Boss::Draw()
{
    DrawTexture(BossImage[BossbulletFrame], x, y, WHITE);
}

void Boss::DrawDefeat()
{
    DrawTexture(BossDefeatImage[BossDefeatFrame], x, y, WHITE);
}

void Boss::Shoot(Sound BossGun)
{
    if (BossbulletFrame == 9)
    {
        PlaySound(BossGun);
        for (int j = 0; j < 3; j++)
        {
            if (!BossBullet[j].GetActive())
            {
                BossBullet[j].SetActive(true);
                BossBullet[j].SetX(x);
                BossBullet[j].SetY(y + (BossHeight / 2) - 15);
                BossBullet[j].SetVelX(-8);
                BossBullet[j].SetVelY(0);
                break;
            }
        }
    }
    for (int j = 0; j < 3; j++)
    {
        if (BossBullet[j].GetActive())
        {
            BossBullet[j].SetX(BossBullet[j].GetX() + BossBullet[j].GetVelX());
            DrawTexture(BossBullet[j].GetImage(), BossBullet[j].GetX(), BossBullet[j].GetY(), WHITE);
            if (BossBullet[j].GetX()< 0)
            {
                BossBullet[j].SetActive(false);
            }
        }
    }
}

void Boss::BulletAndPlayerCollision(Shield& S, Player& P, Blood& B)
{
    for (int i = 0; i < 3; i++)
    {
        if (BossBullet[i].GetActive())
        {
            Rectangle r;
            r.x = (float)BossBullet[i].GetX();
            r.y = (float)BossBullet[i].GetY();
            r.width = (float)BossBullet[i].GetWidth();
            r.height = (float)BossBullet[i].GetHeight();

            BossBullet[i].SetCollider(r);

            if (CheckCollisionRecs(BossBullet[i].GetCollider(),P.GetCollider()))
            {
                if (S.GetActive()&&S.GetHealth()> 0)
                {
                    S.SetHealth(S.GetHealth() - 10);
                    BossBullet[i].SetActive(false);
                    if (S.GetHealth()<= 0)
                    {
                       S.SetActive(false);
                    }
                }
                else
                {
                    P.SetHealth(P.GetHealth() - 15);
                    B.SetIsBlood(true);
                    B.SetBloodTime(30);
                }
                BossBullet[i].SetActive(false);
            }
        }
    }
}

void Boss::UpdateCollider()
{
    BossCollider.x = (float)x;
    BossCollider.y = (float)y;
    BossCollider.width = (float)BossWidth;
    BossCollider.height = (float)BossHeight;
}

// Getters
int Boss::GetX() const
{
    return x;
}

int Boss::GetY() const
{
    return y;
}

float Boss::GetHealth() const
{
    return BossHealth;
}

Rectangle Boss::GetCollider() const
{
    return BossCollider;
}

Texture2D Boss::GetImage(int idx) const
{
    return BossImage[idx];
}

Texture2D Boss::GetDefeatImage(int idx) const
{
    return BossDefeatImage[idx];
}

int Boss::GetHeight() const
{
    return BossHeight;
}

int Boss::GetWidth() const
{
    return BossWidth;
}

int Boss::GetTimer() const
{
    return Bosstimer;
}

int Boss::GetBulletFrame() const
{
    return BossbulletFrame;
}

bool Boss::GetActive() const
{
    return BossActive;
}

Bullet* Boss::GetBullets()
{
    return BossBullet;
}

bool Boss::GetDefeated() const
{
    return BossDefeated;
}

int Boss::GetDefeatFrame() const
{
    return BossDefeatFrame;
}

int Boss::GetDefeatTimer() const
{
    return BossDefeatTimer;
}

// Setters
void Boss::SetX(int val)
{
    x = val;
}

void Boss::SetY(int val)
{
    y = val;
}

void Boss::SetHealth(float val)
{
    BossHealth = val;
}

void Boss::SetCollider(const Rectangle& rect)
{
    BossCollider = rect;
}

void Boss::SetImage(int idx, Texture2D img)
{
    BossImage[idx] = img;
}

void Boss::SetDefeatImage(int idx, Texture2D img)
{
    BossDefeatImage[idx] = img;
}

void Boss::SetHeight(int val)
{
    BossHeight = val;
}

void Boss::SetWidth(int val)
{
    BossWidth = val;
}

void Boss::SetTimer(int val)
{
    Bosstimer = val;
}

void Boss::SetBulletFrame(int val)
{
    BossbulletFrame = val;
}

void Boss::SetActive(bool val)
{
    BossActive = val;
}

void Boss::SetDefeated(bool val)
{
    BossDefeated = val;
}

void Boss::SetDefeatFrame(int val)
{
    BossDefeatFrame = val;
}

void Boss::SetDefeatTimer(int val)
{
    BossDefeatTimer = val;
}