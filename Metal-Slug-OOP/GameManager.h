#pragma once
#include <iostream>
#include <raylib.h>
#include "Player.h"
#include "Blood.h"
#include "Bullet.h"
#include "EnemyParent.h"
#include "Boss.h"
#include "Shield.h"
#include "BG.h"
#include "Enemy.h"
#include "EnemyMan.h"
#include "Helicopter.h"
#include "Zombie.h"

class GameManager
{
    Player P;
    Blood B;
    Bullet bullets[3];
    Bullet enemyManBullets[3];
    Bullet enemyBullets[3];
    Bullet HeliBullets[3];
    Enemy E;
    EnemyMan enemyMan;
    Helicopter helicopter;
    Boss BEnemy;
    Shield S;
    BG b1, b2;
    Texture2D bg1, bg2, bg5, Title;
    Music bgIntro, bgMusic;
    Sound BulletSound, BossGun;
    int level;
    int score;
    int ScreenTimer;
    bool changeBGonce;
    bool GameStart;
    bool ShootHappen;
    int ShootFrame;
    int LegFrame;
    float PSpeed;
    bool Jump;
    bool EndingMenu;
    int shootTimer;

    bool SmokeActive;
    float SmokeTimer;
    Sound SmokeSound;
    Sound CoughSound;
    int SmokePhase;

    Zombie zombies[5];

    Texture2D knifeImage;
    Sound knifeSound;
    bool knifeActive;
    int knifeTimer;
    Rectangle knifeCollider;

public:

    GameManager();
    void Init();
    void Run();
    void DrawBackground();
    void DrawLevelInfo();
    void HealthBar(Player& P);
    void BossHealth(Boss& BEnemy);
    void ShieldHealthBar(Shield& S);
    void PlayerBulletAndEnemyCollisionCheck();
    void DrawUI();
    void HandleLevelTransition();
    void HandlePlayerMovement();
    void HandlePlayerShooting();
    void HandleSmokeLevel();

    void HandleEnemyBulletCollision();
    void HandleBossLogic();
    void HandleRespawns();
    void UpdateBackgroundScroll();
    bool HandleGameOver();
    bool HandleVictory();
    void ShowTitleScreen();
    void ShowStartMenu();
    void HandleZombieLevel();
    void HandleKnifeZombieCollision();


};