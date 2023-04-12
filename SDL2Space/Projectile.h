#pragma once
// Projectile.h
#pragma once
#include <SDL.h>
#include "Spritesheet.h"
#include "GameObject.h"
class Projectile : public GameObject{
public:
    Projectile(Spritesheet* spritesheet, float x, float y, float speed);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);

    bool isOffscreen() const;

     SDL_Rect& GetDstRect() { return m_dstRect; }


private:
    Spritesheet* m_spritesheet;
    SDL_Rect m_srcRect;
    float m_speed;

    int m_currentframe;
    float m_animationSpeed;
    float m_animationTimer;
};