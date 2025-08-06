#pragma once
#include <raylib.h>

class Blood;
class BG;
class EnemyParent;
class Bullet;

class Player
{
    int x[3], y[3];
    bool isAlive;
    float PHealth;
    Rectangle PCollider;
    Texture2D PImage[10];
    int PHeight[2], PWidth[2];
public:
    Player();
    void LoadImages();
    void Move(int& FrameCount, int& LegFrame, float& PSpeed, bool& Jump, int level, BG& b1, BG& b2, EnemyParent& E, EnemyParent& EnemyMan, EnemyParent& Helicopter);
    void Shoot(Bullet bullets[], bool& ShootHappen, Sound BulletSound, EnemyParent& Helicopter);
    void Draw(Blood& B, int LegFrame, int shootTimer);
    void TakeDamage(float dmg, Blood& B);
    void UpdateCollider();

    // Getters
    int GetX(int idx) const;
    int GetY(int idx) const;
    bool GetIsAlive() const;
    float GetHealth() const;
    Rectangle GetCollider() const;
    Texture2D GetImage(int idx) const;
    int GetHeight(int idx) const;
    int GetWidth(int idx) const;

    // Setters
    void SetX(int idx, int val);
    void SetY(int idx, int val);
    void SetIsAlive(bool val);
    void SetHealth(float val);
    void SetCollider(const Rectangle& rect);
    void SetImage(int idx, Texture2D img);
    void SetHeight(int idx, int val);
    void SetWidth(int idx, int val);
};