#include "Player.h"
#include "Blood.h"
#include "BG.h"
#include "EnemyParent.h"
#include "Bullet.h"
#include <raylib.h>
#include <raymath.h>

Player::Player()
{
    for (int i = 0; i < 3; i++)
    {
        x[i] = 0;
        y[i] = 0;
    }
    isAlive = true;
    PHealth = 100.0f;
    for (int i = 0; i < 10; i++)
        PImage[i] = { 0 };
    for (int i = 0; i < 2; i++)
    {
        PHeight[i] = 0;
        PWidth[i] = 0;
    }
    PCollider = { 0, 0, 0, 0 };
}

void Player::LoadImages()
{
    PImage[0] = LoadTexture("PlayerBody.png");
    PHeight[0] = 150; PWidth[0] = 100;
    PImage[1] = LoadTexture("Leg1.png");
    PImage[2] = LoadTexture("Leg2.png");
    PImage[3] = LoadTexture("Leg3.png");
    PImage[4] = LoadTexture("Leg4.png");
    PImage[5] = LoadTexture("Leg5.png");
    PHeight[1] = 80; PWidth[1] = 60;
    PImage[6] = LoadTexture("Player_Shoot.png");

    x[0] = PWidth[0] - 5; y[0] = 600 - PHeight[0] + 25;
    x[1] = PWidth[1] + 20; y[1] = 600 - PHeight[1] - 20;
    x[2] = PWidth[0] - 5; y[2] = 600 - PHeight[0] - 15;
}

void Player::Move(int& FrameCount, int& LegFrame, float& PSpeed, bool& Jump, int level, BG& b1, BG& b2, EnemyParent& E, EnemyParent& EnemyMan, EnemyParent& Helicopter)
{
    if (IsKeyDown(KEY_D))
    {
        FrameCount++;
        if (FrameCount % 10 == 0)
        {
            LegFrame++;
            if (LegFrame > 5)
            {
                LegFrame = 1;
            }
        }

        if (x[0] < 200)
        {
            x[0] += 3;
            x[1] += 3;
            x[2] += 3;
        }
        else
        {
            b1.SetCol(b1.GetCol() - 3);
            b2.SetCol(b2.GetCol() - 3);
            E.SetX(E.GetX() - 3);
            EnemyMan.SetX(EnemyMan.GetX() - 3);

            if (level == 2)
            {
                Helicopter.SetX(Helicopter.GetX() - 3);
            }
            FrameCount++;
            if (FrameCount % 10 == 0)
            {
                LegFrame++;
                if (LegFrame > 5)
                {
                    LegFrame = 1;
                }
            }
        }
    }
    else if (IsKeyDown(KEY_A))
    {
        FrameCount++;
        if (FrameCount % 10 == 0)
        {
            LegFrame++;
            if (LegFrame > 5)
            {
                LegFrame = 1;
            }
        }

        if (x[0] > 0)
        {
            x[0] -= 3;
            x[1] -= 3;
            x[2] -= 3;
            if (x[0] < 0)
            {
                x[0] = 0;
                x[1] = 0;
                x[2] = 0;
            }
        }
    }
    else
    {
        FrameCount = 0;
        LegFrame = 1;
    }

    if (IsKeyPressed(KEY_W) && !Jump)
    {
        PSpeed = -15;
        Jump = true;
    }
    y[0] += PSpeed;
    y[1] += PSpeed;
    y[2] += PSpeed;
    PSpeed += 0.5f;
    if (y[0] >= 600 - PHeight[0] + 25)
    {
        y[0] = 600 - PHeight[0] + 25;
        y[1] = 600 - PHeight[1] - 25;
        y[2] = 600 - PHeight[0] - 15;
        PSpeed = 0;
        Jump = false;
    }
}

void Player::Shoot(Bullet bullets[], bool& ShootHappen, Sound BulletSound, EnemyParent& Helicopter)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        ShootHappen = true;
        PlaySound(BulletSound);
        for (int i = 0; i < 3; i++)
        {
            if (!bullets[i].GetActive())
            {
                bullets[i].SetActive(true);
                bullets[i].SetX(x[0] + PWidth[0] - 30);
                bullets[i].SetY(y[0] + 7);
                bullets[i].SetVelX(10);
                bullets[i].SetVelY(0);
                break;
            }
        }
    }
    if (IsKeyPressed(KEY_E))
    {
        ShootHappen = true;
        PlaySound(BulletSound);
        for (int i = 0; i < 3; i++)
        {
            if (!bullets[i].GetActive())
            {
                bullets[i].SetActive(true);
                bullets[i].SetX(x[0] + PWidth[0] - 30);
                bullets[i].SetY(y[0] + 7);
                float xChange = Helicopter.GetX()- bullets[i].GetX();
                float yChange = Helicopter.GetY()- bullets[i].GetY();
                bullets[i].SetVelX(xChange / 40.0f);
                bullets[i].SetVelY(yChange / 40.0f);
                break;
            }
        }
    }
}

void Player::Draw(Blood& B, int LegFrame, int shootTimer)
{
    B.SetX(x[0] - 27);
    B.SetY(y[0] - 25);
    B.Show();
    DrawTexture(PImage[LegFrame], x[1], y[1], WHITE);

    if (shootTimer > 0)
    {
        DrawTexture(PImage[6], x[2], y[2], WHITE);
    }
    else
    {
        DrawTexture(PImage[0], x[0], y[0], WHITE);
    }
}


void Player::TakeDamage(float dmg, Blood& B)
{
    PHealth -= dmg;
    if (PHealth < 0) 
    {
        PHealth = 0;
    }
    B.SetIsBlood(true);
    B.SetBloodTime(30);
}

void Player::UpdateCollider()
{
    PCollider = { (float)x[0], (float)y[0], (float)PWidth[0] - 30, (float)(PHeight[0] + PHeight[1]) - 130 };
}

// Getters
int Player::GetX(int idx) const
{
    return x[idx]; 
}
int Player::GetY(int idx) const 
{ 
    return y[idx]; 
}
bool Player::GetIsAlive() const 
{ 
    return isAlive; 
}
float Player::GetHealth() const 
{ 
    return PHealth; 
}
Rectangle Player::GetCollider() const 
{ 
    return PCollider; 
}
Texture2D Player::GetImage(int idx) const 
{
    return PImage[idx]; 
}
int Player::GetHeight(int idx) const 
{ 
    return PHeight[idx]; 
}
int Player::GetWidth(int idx) const 
{ 
    return PWidth[idx]; 
}

// Setters
void Player::SetX(int idx, int val) 
{ 
    x[idx] = val; 
}
void Player::SetY(int idx, int val) 
{ 
    y[idx] = val; 
}
void Player::SetIsAlive(bool val) 
{ 
    isAlive = val; 
}
void Player::SetHealth(float val) 
{ 
    PHealth = val; 
}
void Player::SetCollider(const Rectangle& rect) 
{ 
    PCollider = rect; 
}
void Player::SetImage(int idx, Texture2D img) 
{ 
    PImage[idx] = img; 
}
void Player::SetHeight(int idx, int val) 
{ 
    PHeight[idx] = val; 
}
void Player::SetWidth(int idx, int val) 
{
    PWidth[idx] = val; 
}