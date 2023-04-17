#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Player.h"
#include "Spritesheet.h"
#include "Background.h"
#include "Enemy.h"
#include "SinusoidalEnemy.h"
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
    void UpdateScoreTexture();
    void removeSinEnemy(SinusoidalEnemy* enemy);
private:
    //...
    TTF_Font* m_font;
    int m_score;
    SDL_Color m_textColor;
    SDL_Surface* m_scoreSurface;
    SDL_Texture* m_scoreTexture;
    SDL_Rect m_scoreRect;


    SDL_Renderer* m_renderer;
    std::shared_ptr<Spritesheet> playerspritesheet;
    std::shared_ptr<Spritesheet> projectilespritesheet;
    std::shared_ptr<Spritesheet> enemyspritesheet;
    std::shared_ptr<Spritesheet> mediumenemyspritesheet;
    std::shared_ptr<Spritesheet> bigenemyspritesheet;
    std::shared_ptr<Spritesheet> explosionspritesheet;
    std::unique_ptr<Player> player;
    std::unique_ptr<Background> background;

    std::vector<std::shared_ptr<GameObject>> gameobjects;
    std::vector<std::shared_ptr<Enemy>> enemyobjects;
    float enemyspawntimer;
    float enemyspawninterval;

    void SpawnEnemy();

    float spawntimer;
    int spawnsequence;
};
