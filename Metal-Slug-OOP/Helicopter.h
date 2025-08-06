#pragma once
#include"EnemyParent.h"

class Helicopter : public EnemyParent
{
public:
    Helicopter();
    void LoadImage() override;
    void Move() override;
    void Shoot(Bullet bullets[]) override;
    void Draw() override;
    void Respawn() override;
    void HandleBullets(Bullet bullets[]) override;
};
