#include "GameManager.h"
#include <raylib.h>

GameManager::GameManager()
{
    level = 1;
    score = 0;
    ScreenTimer = 120;
    changeBGonce = false;
    GameStart = false;
    ShootHappen = false;
    ShootFrame = 0;
    LegFrame = 1;
    PSpeed = 0;
    Jump = false;
    EndingMenu = false;

    shootTimer = 0;
}

void GameManager::Init()
{
    srand(time(0));
    InitAudioDevice();

    bgIntro = LoadMusicStream("bgIntro.mp3");
    bgMusic = LoadMusicStream("bgMusic.mp3");
    BulletSound = LoadSound("Bullet_Sound.mp3");
    BossGun = LoadSound("Boss_Gun_Sound.mp3");

    SmokeSound = LoadSound("Smoke_Sound.mp3");
    CoughSound = LoadSound("Cough_Sound.mp3");

    SetMusicVolume(bgIntro, 1.0f);
    SetMusicVolume(bgMusic, 1.0f);
    SetSoundVolume(BulletSound, 1.0f);
    SetSoundVolume(BossGun, 5.0f);

    SetSoundVolume(SmokeSound, 3.0f);
    SetSoundVolume(CoughSound, 4.0f);

    E.LoadImage();
    enemyMan.LoadImage();
    helicopter.LoadImage();

    for (int i = 0; i < 3; i++)
    {
        bullets[i].Load("Bullet.png",P.GetX(0),P.GetY(0));
        enemyBullets[i].Load("eBullet1.png", E.GetX(), E.GetY());
        enemyManBullets[i].Load("eBullet2.png", enemyMan.GetX(), enemyMan.GetY());
        HeliBullets[i].Load("eBullet3.png", helicopter.GetX(), helicopter.GetY());
        BEnemy.GetBullets()[i].Load("eBullet4.png", BEnemy.GetX(), BEnemy.GetY());
    }

    S.SetImage(LoadTexture("Shield.png"));
    P.LoadImages();
    B.LoadImages();
    BEnemy.LoadImages();

    bg1 = LoadTexture("Back1.png");
    bg1.height = 600; bg1.width = 1000;
    bg2 = LoadTexture("Back2.png");
    bg2.height = 600; bg2.width = 1000;
    bg5 = LoadTexture("bg5.png");
    bg5.height = 600; bg5.width = 1000;
    Title = LoadTexture("Title.png");

    E.SetX(1000);
    E.SetY(600 - E.GetHeight() + 25);
    enemyMan.SetX(1000);
    enemyMan.SetY(600 - enemyMan.GetHeight() + 25);
    helicopter.SetX(1000);
    helicopter.SetY(helicopter.GetHeight() - 20);
   b1.SetRow(0);b1.SetCol(0);
   b2.SetRow(0);b2.SetCol(1000);

    for (int i = 0; i < 5; i++)
    {
        zombies[i].LoadImage();
        zombies[i].SetVisible(false);
    }

    knifeImage = LoadTexture("Knife.png");
    knifeSound = LoadSound("Knife_Stab.mp3");
    SetSoundVolume(knifeSound, 1.0f);
    knifeActive = false;
    knifeTimer = 0;
}

void GameManager::DrawBackground()
{
    if (level < 4)
    {
        DrawTexture(bg1,b1.GetCol(),b1.GetRow(), WHITE);
        DrawTexture(bg2,b2.GetCol(),b2.GetRow(), WHITE);
    }
    else
    {
        DrawTexture(bg5, 0, 0, WHITE);
    }
}

void GameManager::DrawLevelInfo()
{
    DrawText(TextFormat("LEVEL: %d", level), 1000 - 200, 45, 20, WHITE);
}

void GameManager::HealthBar(Player& P)
{
    DrawRectangle(20, 20, 400, 20, RED);
    DrawRectangle(20, 20, (int)(400 * (P.GetHealth()/ 100.0f)), 20, GREEN);
}

void GameManager::BossHealth(Boss& BEnemy)
{
    DrawRectangle(1000 / 2, 70, 400, 20, BLACK);
    DrawRectangle(1000 / 2, 70, (int)(200 * (BEnemy.GetHealth()/ 100.0f)), 20, YELLOW);
}
void GameManager::ShieldHealthBar(Shield& S)
{
    DrawRectangle(20, 50, 200, 15, DARKGRAY);
    DrawRectangle(20, 50, (int)(2 *S.GetHealth()), 15, SKYBLUE);
    DrawText(TextFormat("Shield: %.0f",S.GetHealth()), 230, 50, 15, WHITE);
}

void GameManager::DrawUI()
{
    DrawText(TextFormat("SCORE: %d", score), 1000 - 200, 15, 20, WHITE);
    HealthBar(P);
    ShieldHealthBar(S);
    if (level == 5)
    {
        BossHealth(BEnemy);
    }
}

void GameManager::HandleLevelTransition()
{
    if (score >= 15 && score < 35 && level == 1 && !changeBGonce)
    {
        changeBGonce = true;
        bg1 = LoadTexture("bg3.png");
        bg2 = LoadTexture("bg4.png");
        bg1.height = 600;
        bg1.width = 1000;
        bg2.height = 600;
        bg2.width = 1000;
    }
    changeBGonce = false;

    if (score >= 60 && level == 4 && !changeBGonce)
    {
        changeBGonce = true;
        bg1 = bg5;
    }

    if (score >= 15 && score < 35 && level == 1)
    {
        level = 2;
        ScreenTimer = 120;
        while (ScreenTimer > 0)
        {
            UpdateMusicStream(bgMusic);
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("LEVEL 2", 1000 / 2 - 100, 600 / 2 - 50, 40, WHITE);
            DrawText("Use E to destroy the Helicopter!", 1000 / 2 - 250, 600 / 2 + 20, 30, WHITE);
            ScreenTimer--;
            EndDrawing();
        }

        E.Respawn();
        enemyMan.Respawn();
        helicopter.Respawn();
    }

    if (score >= 35 && level == 2) 
    {
        level = 3;
        ScreenTimer = 120;
        while (ScreenTimer > 0) 
        {
            UpdateMusicStream(bgMusic);
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("LEVEL 3", 1000 / 2 - 100, 600 / 2 - 50, 40, WHITE);
            DrawText("Toxic Rush! Survive the deadly smoke!", 1000 / 2 - 250, 600 / 2 + 20, 30, GREEN);
            ScreenTimer--;
            EndDrawing();
        }
        SmokeActive = true;
        PlaySound(SmokeSound);
        PlaySound(CoughSound);
        E.Respawn();
        enemyMan.Respawn();
        helicopter.Respawn();
    }

    if (score >= 60 && level == 3)
    {
        level = 4;
        ScreenTimer = 120;
        while (ScreenTimer > 0)
        {
            UpdateMusicStream(bgMusic);
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("LEVEL 4", 1000 / 2 - 100, 600 / 2 - 50, 40, WHITE);
            DrawText("Zombie Night! Survive the horde! \n ONLY KNIFE \n NO SHIELD", 1000 / 2 - 250, 600 / 2 + 20, 30, GREEN);
            ScreenTimer--;
            EndDrawing();
        }
        for (int i = 0; i < 5; i++)
        {
            zombies[i].SetVisible(false);
        }
        E.Respawn();
        enemyMan.Respawn();
        helicopter.Respawn();
    }

    if (score >= 100 && level == 4)
    {
        level = 5;
        ScreenTimer = 120;
        while (ScreenTimer > 0)
        {
            UpdateMusicStream(bgMusic);
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Final Level", 1000 / 2 - 100, 600 / 2 - 50, 40, WHITE);
            DrawText("Defeat The Final Boss!", 1000 / 2 - 250, 600 / 2 + 20, 30, RED);
            ScreenTimer--;
            EndDrawing();
        }
        
        E.Respawn();
        enemyMan.Respawn();
        S.SetHealth(100.0f);
        S.SetActive(true);
    }
}

void GameManager::HandleSmokeLevel()
{
    if (!SmokeActive)
    {
        return;
    }

    if (!IsSoundPlaying(SmokeSound))
    {
        PlaySound(SmokeSound);
    }

    SmokeTimer += GetFrameTime();
    if (SmokeTimer > 5 && SmokePhase == 0)
    {
        SmokePhase = 1; 
    }
    if (SmokeTimer > 10 && SmokePhase == 1)
    { 
        SmokePhase = 2; 
    }

    static float HealthDrainTimer = 0.0f;
    HealthDrainTimer += GetFrameTime();
    float drain = 1.0f;
    if (SmokePhase == 1) 
    {
        drain = 2.0f;
    }
    if (SmokePhase == 2) 
    {
        drain = 3.0f;
    }
    if (HealthDrainTimer >= 1.0f) 
    {
        P.SetHealth(P.GetHealth() - drain);
        HealthDrainTimer = 0.0f;
    }

    if (!IsSoundPlaying(CoughSound))
    {
        PlaySound(CoughSound);
    }
    DrawText("TOXIC SMOKE! KILL ENEMIES TO SURVIVE!", 1000 / 2 - 50, 20, 15, GREEN);
}

void GameManager::HandlePlayerMovement()
{
    P.Move(ShootFrame, LegFrame, PSpeed, Jump, level, b1, b2, E, enemyMan, helicopter);
}

void GameManager::HandlePlayerShooting()
{
    if (level == 4)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            knifeActive = true;
            knifeTimer = 10;
            PlaySound(knifeSound);

            knifeCollider = { (float)P.GetX(0)+P.GetWidth(0)- 50, (float)P.GetY(0)+ 40, 80, 20 };
        }
    }
    else
    {
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_E))
        {
            ShootHappen = true;
            shootTimer = 8;
        }
        P.Shoot(bullets, ShootHappen, BulletSound, helicopter);
    }
}

void GameManager::HandleEnemyBulletCollision()
{
    for (int i = 0; i < 3; i++)
    {
        if (enemyBullets[i].GetActive())
        {
            if (CheckCollisionRecs(enemyBullets[i].GetCollider(),P.GetCollider()))
            {
                if (S.GetActive()&&S.GetHealth()> 0)
                {
                    S.SetHealth(S.GetHealth() - 2);
                    if (S.GetHealth()<= 0)
                    {
                        S.SetActive(false);
                    }
                }
                else
                {
                    P.SetHealth(P.GetHealth() - 1);
                    B.SetIsBlood(true);
                    B.SetBloodTime(30);
                }
                enemyBullets[i].SetActive(false);
            }
        }
        if (enemyManBullets[i].GetActive())
        {
            if (CheckCollisionRecs(enemyManBullets[i].GetCollider(),P.GetCollider()))
            {
                if (S.GetActive()&&S.GetHealth()> 0)
                {
                    S.SetHealth(S.GetHealth() - 2);
                    if (S.GetHealth()<= 0) 
                    {
                        S.SetActive(false);
                    }
                }
                else
                {
                    P.SetHealth(P.GetHealth() - 1);
                    B.SetIsBlood(true);
                    B.SetBloodTime(30);
                }
                enemyManBullets[i].SetActive(false);
            }
        }
        if (HeliBullets[i].GetActive())
        {
            if (CheckCollisionRecs(HeliBullets[i].GetCollider(),P.GetCollider()))
            {
                if (S.GetActive() && S.GetHealth() > 0)
                {
                    S.SetHealth(S.GetHealth() - 3);
                    if (S.GetHealth()<= 0)
                    {
                        S.SetActive(false);
                    }
                }
                else
                {
                    P.SetHealth(P.GetHealth() - 2);
                }
                HeliBullets[i].SetActive(false);
            }
            else if (HeliBullets[i].GetY() >= 600 - 50 &&
                HeliBullets[i].GetX() >=P.GetX(0)- 100 &&
                HeliBullets[i].GetX() <= P.GetX(0) + 100)
            {
                if (S.GetActive() && S.GetHealth() > 0)
                {
                    S.SetHealth(S.GetHealth() - 2);
                    if (S.GetHealth()<= 0) 
                    {
                        S.SetActive(false);
                    }
                }
                else
                {
                    P.SetHealth(P.GetHealth() - 1);
                }
                HeliBullets[i].SetActive(false);
            }
        }
    }
}

void GameManager::HandleBossLogic()
{
    if (BEnemy.GetHealth()> 0)
    {
        BEnemy.SetTimer(BEnemy.GetTimer() + 1);

        if (BEnemy.GetTimer() % 10 == 0)
        {
            BEnemy.SetBulletFrame(BEnemy.GetBulletFrame() + 1);

            if (BEnemy.GetBulletFrame() > 9)
            {
                BEnemy.SetBulletFrame(0);
            }
        }

        DrawTexture(
            BEnemy.GetImage(BEnemy.GetBulletFrame()),BEnemy.GetX(),BEnemy.GetY(),WHITE);
        BEnemy.Shoot(BossGun);
        BEnemy.BulletAndPlayerCollision(S, P, B);
    }
    else
    {
        BEnemy.SetDefeated(true);
    }
    if (BEnemy.GetDefeated())
    {
        BEnemy.SetDefeatTimer(BEnemy.GetDefeatTimer() + 1);

        if (BEnemy.GetDefeatTimer() % 10 == 0)
        {
            BEnemy.SetDefeatFrame(BEnemy.GetDefeatFrame() + 1);

            if (BEnemy.GetDefeatFrame() > 7)
            {
                BEnemy.SetDefeatFrame(7);
                EndingMenu = true;
            }
        }

        DrawTexture(
            BEnemy.GetDefeatImage(BEnemy.GetDefeatFrame()),BEnemy.GetX(),BEnemy.GetY(),WHITE);

    }
}

void GameManager::HandleRespawns()
{
    if (E.GetX()<= 0) 
    {
        E.Respawn();
    }
    if (enemyMan.GetX()<= 0) 
    {
        enemyMan.Respawn();
    }
    if (helicopter.GetX()<= 0 && level == 2) 
    {
        helicopter.Respawn();
    }
}

void GameManager::UpdateBackgroundScroll()
{

    if (b1.GetCol()<= -1000)
    {
        b1.SetCol(b2.GetCol() + 1000);
    }
    if (b2.GetCol()<= -1000)
    {
        b2.SetCol(b1.GetCol() + 1000);
    }
}

bool GameManager::HandleGameOver()
{
    if (P.GetHealth()<= 0)
    {
        DrawText("GAME OVER", 1000 / 2 - 100, 600 / 2, 40, RED);
        EndDrawing();
        while (!IsKeyPressed(KEY_ESCAPE))
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("GAME OVER", 1000 / 2 - 100, 600 / 2 - 100, 40, RED);
            DrawText("Press escape to exit", 1000 / 2 - 120, 600 / 2 - 120 + 60, 30, WHITE);
            EndDrawing();
        }
        return true;
    }
    return false;
}

bool GameManager::HandleVictory()
{
    if (EndingMenu)
    {
        DrawText("YOU DEFEATED THE BOSS! ", 1000 / 2 - 100, 600 / 2, 40, RED);
        EndDrawing();
        while (!IsKeyPressed(KEY_ESCAPE))
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("YOU WIN...", 1000 / 2 - 100, 600 / 2 - 100, 40, RED);
            DrawText("Press escape to exit", 1000 / 2 - 120, 600 / 2 - 120 + 60, 30, WHITE);
            EndDrawing();
        }
        return true;
    }
    return false;
}

void GameManager::ShowTitleScreen()
{
    for (int i = 1; i <= 100; i++)
    {
        UpdateMusicStream(bgIntro);
        Title.height = 4 * i, Title.width = 6 * i;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(Title, 1000 / 2 - Title.width / 2, 20, WHITE);
        EndDrawing();
    }
}

void GameManager::ShowStartMenu()
{
    while (!WindowShouldClose() && !GameStart)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(Title, 1000 / 2 - Title.width / 2, 20, WHITE);
        DrawText("PRESS ENTER TO START.", 1000 / 2 - 180, 600 / 2 + 150, 30, WHITE);
        DrawText("Controls>> (D)forward..(W)Jump..(Space)Fire", 1000 / 2 - 480, 600 / 2 + 200, 30, WHITE);
        DrawText("(E)Diagonal Fire..(Left Shift)..Shield", 1000 / 2 - 480, 600 / 2 + 250, 30, WHITE);

        if (IsKeyPressed(KEY_ENTER))
        {
            StopMusicStream(bgIntro);
            PlayMusicStream(bgMusic);
            GameStart = true;
        }
        EndDrawing();
    }
}

void GameManager::PlayerBulletAndEnemyCollisionCheck()
{
    for (int i = 0; i < 3; i++)
    {
        if (bullets[i].GetActive())
        {
            if (bullets[i].GetVelY()!= 0)
            {
                bullets[i].SetX(bullets[i].GetX() + (int)bullets[i].GetVelX());
                bullets[i].SetY(bullets[i].GetY() + (int)bullets[i].GetVelY());
            }
            else
            {
                bullets[i].SetX(bullets[i].GetX() + 10);
            }

            if (bullets[i].GetX() < 0 || bullets[i].GetX()> 1000 ||
                bullets[i].GetY()< 0 || bullets[i].GetY()> 600)
            {
                bullets[i].SetActive(false);
                continue;
            }
            Rectangle collider;
            collider.x = (float)bullets[i].GetX();
            collider.y = (float)bullets[i].GetY();
            collider.width = (float)bullets[i].GetWidth();
            collider.height = (float)bullets[i].GetHeight();

            bullets[i].SetCollider(collider);

            if (CheckCollisionRecs(bullets[i].GetCollider(), E.GetCollider()))
            {
                score++;
                bullets[i].SetActive(false);
                E.Respawn();
            }
            else if (CheckCollisionRecs(bullets[i].GetCollider(), enemyMan.GetCollider()))
            {
                score++;
                bullets[i].SetActive(false);
                enemyMan.Respawn();
            }
            else if (CheckCollisionRecs(bullets[i].GetCollider(), helicopter.GetCollider()))
            {
                score++;
                bullets[i].SetActive(false);
                helicopter.Respawn();
            }
            else if (level == 5 && CheckCollisionRecs(bullets[i].GetCollider(), BEnemy.GetCollider()))
            {
                score++;
                BEnemy.SetHealth(BEnemy.GetHealth() - 5);
                bullets[i].SetActive(false);
            }
        }
    }
}

void GameManager::HandleZombieLevel()
{
    DrawTexture(bg1,b1.GetCol(),b1.GetRow(), WHITE);
    DrawTexture(bg2,b2.GetCol(),b2.GetRow(), WHITE);

    DrawRectangle(0, 0, 1000, 600, Fade(BLACK, 0.95f));
    Vector2 spotCenter = {P.GetX(0) + 50,P.GetY(0)+ 75 };
    BeginBlendMode(BLEND_ADDITIVE);
    DrawCircleV(spotCenter, 120, Fade(WHITE, 0.96f));
    EndBlendMode();
    for (int i = 0; i < 5; i++)
    {
        if (!zombies[i].GetVisible())
        {
            if (rand() % 100 < 2)
            {
                zombies[i].RespawnNearPlayer(P.GetX(0), P.GetY(0));
                zombies[i].SetVisible(true);
            }
        }
        else
        {
            if (CheckCollisionPointCircle(
                { (float)zombies[i].GetX()+ zombies[i].GetWidth()/ 2, (float)zombies[i].GetY()+ zombies[i].GetHeight()/ 2 },
                spotCenter, 180))
            {
                zombies[i].SetVisible(true);
            }
            zombies[i].Move();
            zombies[i].Draw();

            for (int b = 0; b < 3; b++)
            {
                if (bullets[b].GetActive() && zombies[i].GetVisible())
                {
                    if (CheckCollisionRecs(bullets[b].GetCollider(), zombies[i].GetCollider()))
                    {
                        score++;
                        bullets[b].SetActive(false);
                        zombies[i].SetVisible(false);
                    }
                }
            }

            if (zombies[i].GetVisible()&& CheckCollisionRecs(zombies[i].GetCollider(),P.GetCollider()))
            {
                P.SetHealth(P.GetHealth() - 5);
                B.SetIsBlood(true);
                B.SetBloodTime(30);
                zombies[i].SetVisible(false);
            }

            if (zombies[i].GetX()< -zombies[i].GetWidth())
            {
                zombies[i].SetVisible(false);
            }
        }
    }
    S.SetActive(false);
    S.SetHealth(0);
}

void GameManager::HandleKnifeZombieCollision()
{
    if (level != 4 || !knifeActive)
    {
        return;
    }
    for (int i = 0; i < 5; i++)
    {
        if (zombies[i].GetVisible()&& CheckCollisionRecs(knifeCollider, zombies[i].GetCollider()))
        {
            zombies[i].SetVisible(false);
            score ++;
        }
    }
}

void GameManager::Run()
{
    InitWindow(1000, 600, "METAL SLUG");
    SetTargetFPS(60);

    Init();

    PlayMusicStream(bgIntro);
    ShowTitleScreen();
    ShowStartMenu();

    while (!WindowShouldClose())
    {
        ShootFrame++;
        if (ShootFrame >= 60)
        {
            ShootFrame = 0;
        }
        UpdateMusicStream(bgMusic);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawBackground();
        if (level == 4)
        {
            HandleZombieLevel();
        }
        else if (level == 3 && SmokeActive)
        {
            HandleSmokeLevel();
        }
        if (level == 4 && knifeActive)
        {
            DrawTexture(knifeImage, (int)knifeCollider.x, (int)knifeCollider.y, WHITE);
        }
        P.Draw(B, LegFrame, shootTimer);
        if (shootTimer > 0)
        {
            shootTimer--;
        }
        if(level!=4)
        {
            E.Draw();
            enemyMan.Draw();
        }
        if (level == 2 || level == 3)
        {
            helicopter.Draw();
        }
        S.Draw(P);

        DrawUI();

        DrawLevelInfo();

        HandleLevelTransition();
        if(level!=4)
        {
            E.Move();
            enemyMan.Move();
            if (level == 2 || level == 3)
            {
                helicopter.Move();
            }

            E.Shoot(enemyBullets);
            enemyMan.Shoot(enemyManBullets);
            if (level == 2 || level == 3)
            {
                helicopter.Shoot(HeliBullets);
            }
        }

        if (level == 5)
        {
            HandleBossLogic();
        }

        HandlePlayerMovement();
        HandlePlayerShooting();
        if (level == 4)
        {
            HandleKnifeZombieCollision();
            if (knifeTimer > 0)
            {
                knifeTimer--;
                if (knifeTimer == 0)
                {
                    knifeActive = false;
                }
            }
        }

        P.UpdateCollider();
        E.UpdateCollider();
        enemyMan.UpdateCollider();
        helicopter.UpdateCollider();
        BEnemy.UpdateCollider();


        if (level == 4)
        {
            S.SetActive(false);
        }
        else if (IsKeyDown(KEY_LEFT_SHIFT) &&S.GetHealth()> 0)
        {
            S.SetActive(true);
        }
        else
        {
            S.SetActive(false);
        }
        if (level != 4)
        {
            E.HandleBullets(enemyBullets);
            enemyMan.HandleBullets(enemyManBullets);
            if (level == 2 || level == 3)
            {
                helicopter.HandleBullets(HeliBullets);
            }
        }

        if(level!=4)
        {
            HandleEnemyBulletCollision();
        }

            PlayerBulletAndEnemyCollisionCheck();

            if(level!=4)
            {
                for (int i = 0; i < 3; i++)
                {
                    bullets[i].Draw();
                }
            }

        UpdateBackgroundScroll();

        HandleRespawns();

        if (HandleGameOver())
        {
            break;
        }
        if (HandleVictory())
        {
            break;
        }
        if (level == 3 && SmokeActive)
        {
            DrawRectangle(0, 0, 1000, 600, Fade(GREEN, 0.2));
        }

        EndDrawing();
    }
    CloseWindow();
}