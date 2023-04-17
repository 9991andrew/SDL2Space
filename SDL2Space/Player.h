
#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include <vector>

class Player: public GameObject {
public:
    Player(std::shared_ptr<Spritesheet> spritesheet, std::shared_ptr<Spritesheet> projectilespritesheet, int startX, int startY);

    void handleInput(float deltatime);
    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer);
    //Used to take damage.
    void TakeDamage(int damage);
    std::vector<std::shared_ptr<Projectile>>& getProjectiles() { return m_projectiles;  }
    int GetPlayerHealth() { return playerhealth; }

private:
    std::shared_ptr<Spritesheet> m_playerspritesheet;
    std::shared_ptr<Spritesheet> m_projectilespritesheet;
    int m_playercurrentframe;
    float m_animationspeed;
    float m_animationtimer;

    std::vector<std::shared_ptr<Projectile>> m_projectiles; 
    float m_shootCooldown;
    float m_shootCooldownMax;
    //Life
    int playerhealth;
    int maxplayerhealth;
    //The bar.
    SDL_Rect healthbarrect;
    SDL_Rect healthbarbackground;
    void Shoot();
    void DrawHealthBarRect(SDL_Renderer* renderer);
};
