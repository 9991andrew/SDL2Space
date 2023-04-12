#pragma once

#include <SDL.h>
#include "Player.h"
#include "Spritesheet.h"
#include "Background.h"
#include "Enemy.h"
#include "Explosion.h"
class MainGame {
public:
    MainGame();
    ~MainGame();

    void Init(SDL_Renderer* renderer);
    void HandleInput(float deltatime);
    void Update(float deltaTime);
    void Draw();
    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
    void Cleanup();

private:
    SDL_Renderer* m_renderer;
    Spritesheet* playerspritesheet;
    Spritesheet* projectilespritesheet;
    Spritesheet* enemyspritesheet;
    Spritesheet* mediumenemyspritesheet;
    Spritesheet* bigenemyspritesheet;
    Spritesheet* explosionspritesheet;
    Player* player;
    Background* background;

    std::vector<Enemy*> enemies;
    std::vector<Explosion*> explosions;
    float enemyspawntimer;
    float enemyspawninterval;

    void SpawnEnemy();
    float spawntimer;
    int spawnsequence;
};
