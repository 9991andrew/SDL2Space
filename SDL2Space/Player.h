
#pragma once
#include "Projectile.h"
#include <vector>

class Player {
public:
    Player(Spritesheet* spritesheet, int startX, int startY);

    void handleInput(SDL_Event event);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);

private:
    Spritesheet* m_spritesheet;
    int m_x, m_y;
    int m_currentframe;
    float m_animationspeed;
    float m_animationtimer;

    std::vector<Projectile*> m_projectiles;
    float m_shootCooldown;
    float m_shootCooldownMax;
};
