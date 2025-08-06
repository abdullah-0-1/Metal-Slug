#pragma once
#include <raylib.h>

class Player;

class Shield
{
    float health;
    Texture2D SImage;
    bool active;
public:
    Shield();
    void Draw(Player& P);
    void Update();

    // Getters
    float GetHealth() const;
    Texture2D GetImage() const;
    bool GetActive() const;

    // Setters
    void SetHealth(float val);
    void SetImage(Texture2D img);
    void SetActive(bool val);
};