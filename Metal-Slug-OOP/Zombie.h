#pragma once
#include "EnemyParent.h"

class Zombie : public EnemyParent
{
    bool visible;
public:
    Zombie();
    void LoadImage() override;
    void Move() override;
    void Shoot(Bullet bullets[]) override {}
    void Draw() override;
    void RespawnNearPlayer(int playerX, int playerY);
    void HandleBullets(Bullet bullets[]) override {}
    void Respawn() override {};

    // Getter
    bool GetVisible() const;

    // Setter
    void SetVisible(bool val);
};