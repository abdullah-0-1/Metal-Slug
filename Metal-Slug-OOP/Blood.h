#pragma once
#include <raylib.h>

class Player;

class Blood
{
    int x, y;
    Texture2D PBlood[5];
    int BHeight, BWidth;
    int BloodFrame;
    bool IsBlood;
    int BloodTime;

public:
    Blood();
    void LoadImages();
    void Show();
    void Start(int px, int py);

    // Getters
    int GetX() const;
    int GetY() const;
    Texture2D GetBloodImage(int idx) const;
    int GetHeight() const;
    int GetWidth() const;
    int GetBloodFrame() const;
    bool GetIsBlood() const;
    int GetBloodTime() const;

    // Setters
    void SetX(int val);
    void SetY(int val);
    void SetBloodImage(int idx, Texture2D img);
    void SetHeight(int val);
    void SetWidth(int val);
    void SetBloodFrame(int val);
    void SetIsBlood(bool val);
    void SetBloodTime(int val);
};