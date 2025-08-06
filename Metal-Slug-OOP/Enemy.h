#pragma once
#include"EnemyParent.h"

class Enemy : public EnemyParent
{
public:
    Enemy();
    void LoadImage() override;
    void Move() override;
    void Shoot(Bullet bullets[]) override;
    void Draw() override;
    void Respawn() override;
    void HandleBullets(Bullet bullets[]) override;
};
