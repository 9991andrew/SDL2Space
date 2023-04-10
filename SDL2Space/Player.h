
#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include <vector>

class Player: public GameObject {
public:
    Player(Spritesheet* playerspritesheet, Spritesheet* projectilespritesheet, int startX, int startY);

    void handleInput(float deltatime);
    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer);

    const std::vector<Projectile*>& getProjectiles() const { return m_projectiles;  }

private:
    Spritesheet* m_playerspritesheet;
    Spritesheet* m_projectilespritesheet;
    int m_playercurrentframe;
    float m_animationspeed;
    float m_animationtimer;

    std::vector<Projectile*> m_projectiles;
    float m_shootCooldown;
    float m_shootCooldownMax;

    void Shoot();
};
