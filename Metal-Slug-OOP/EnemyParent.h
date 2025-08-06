#pragma once
#include <raylib.h>
#include "Bullet.h"

class EnemyParent
{
protected:
    int x, y;
    Rectangle ECollider;
    float EHealth;
    Texture2D EImage;
    int EHeight, EWidth;
    int timer;
    int bulletFrame;
    int bulletsActive;
public:
    EnemyParent();
    virtual ~EnemyParent() {}

    virtual void LoadImage() = 0;
    virtual void Move() = 0;
    virtual void Shoot(Bullet bullets[]) = 0;
    virtual void Draw() = 0;
    virtual void Respawn() = 0;
    virtual void TakeDamage(float dmg);
    void UpdateCollider();
    virtual void HandleBullets(Bullet bullets[]) = 0;

    int GetX() const;
    int GetY() const;
    Rectangle GetCollider() const;
    float GetHealth() const;
    Texture2D GetImage() const;
    int GetHeight() const;
    int GetWidth() const;
    int GetTimer() const;
    int GetBulletFrame() const;
    int GetBulletsActive() const;

    // Setters
    void SetX(int val);
    void SetY(int val);
    void SetCollider(const Rectangle& rect);
    void SetHealth(float val);
    void SetImage(Texture2D img);
    void SetHeight(int val);
    void SetWidth(int val);
    void SetTimer(int val);
    void SetBulletFrame(int val);
    void SetBulletsActive(int val);
};


