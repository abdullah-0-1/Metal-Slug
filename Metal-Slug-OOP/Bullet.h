#pragma once
#include <raylib.h>

class Bullet
{
    int x, y;
    Texture2D BImage;
    bool active;
    int BHeight, BWidth;
    Rectangle BCollider;
    int vel_x;
    int vel_y;

public:
    Bullet();
    void Load(const char* Fname, int px, int py);
    void Move();
    void Draw();
    void Reset();

    // Getters
    int GetX() const;
    int GetY() const;
    Texture2D GetImage() const;
    bool GetActive() const;
    int GetHeight() const;
    int GetWidth() const;
    Rectangle GetCollider() const;
    int GetVelX() const;
    int GetVelY() const;

    // Setters
    void SetX(int val);
    void SetY(int val);
    void SetImage(Texture2D img);
    void SetActive(bool val);
    void SetHeight(int val);
    void SetWidth(int val);
    void SetCollider(const Rectangle& rect);
    void SetVelX(int val);
    void SetVelY(int val);

};