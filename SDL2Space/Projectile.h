#pragma once
// Projectile.h
#pragma once
#include <SDL.h>
#include "Spritesheet.h"

class Projectile {
public:
    Projectile(Spritesheet* spritesheet, float x, float y, float speed);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);

    bool isOffscreen() const;

private:
    Spritesheet* m_spritesheet;
    SDL_Rect m_srcRect;
    SDL_Rect m_dstRect;
    float m_speed;
};