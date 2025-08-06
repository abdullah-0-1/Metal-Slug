#pragma once
#include <raylib.h>
#include "Bullet.h"

class Shield;
class Player;
class Blood;

class Boss
{
    int x, y;
    float BossHealth;
    Rectangle BossCollider;
    Texture2D BossImage[20];
    Texture2D BossDefeatImage[15];
    int BossHeight, BossWidth;
    int Bosstimer;
    int BossbulletFrame;
    bool BossActive;
    Bullet BossBullet[3];
    bool BossDefeated;
    int BossDefeatFrame;
    int BossDefeatTimer;

public:
    Boss();
    void LoadImages();
    void Draw();
    void DrawDefeat();
    void Shoot(Sound BossGun);
    void BulletAndPlayerCollision(Shield& S, Player& P, Blood& B);
    void UpdateCollider();

    int GetX() const;
    int GetY() const;
    float GetHealth() const;
    Rectangle GetCollider() const;
    Texture2D GetImage(int idx) const;
    Texture2D GetDefeatImage(int idx) const;
    int GetHeight() const;
    int GetWidth() const;
    int GetTimer() const;
    int GetBulletFrame() const;
    bool GetActive() const;
    Bullet* GetBullets();
    bool GetDefeated() const;
    int GetDefeatFrame() const;
    int GetDefeatTimer() const;

    // Setters
    void SetX(int val);
    void SetY(int val);
    void SetHealth(float val);
    void SetCollider(const Rectangle& rect);
    void SetImage(int idx, Texture2D img);
    void SetDefeatImage(int idx, Texture2D img);
    void SetHeight(int val);
    void SetWidth(int val);
    void SetTimer(int val);
    void SetBulletFrame(int val);
    void SetActive(bool val);
    void SetDefeated(bool val);
    void SetDefeatFrame(int val);
    void SetDefeatTimer(int val);
};