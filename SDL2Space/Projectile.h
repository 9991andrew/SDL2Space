#pragma once
// Projectile.h
#pragma once
#include <SDL.h>
#include "Spritesheet.h"
#include "GameObject.h"
class Projectile : public GameObject{
public:
    Projectile(std::shared_ptr<Spritesheet> spritesheet, float x, float y, float vx, float vy);
    ~Projectile();
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);
    bool isOffscreen() const; 

    bool GetHasDamagedPlayer() { return hasdamagedplayer; }
    void SetHasDamagedPlayer(bool x) { this->hasdamagedplayer = x; }
private:
    std::shared_ptr<Spritesheet> m_spritesheet;
    SDL_Rect m_srcRect;
    float m_speed;
    int m_currentframe;
    float m_animationSpeed;
    float m_animationTimer;

    bool hasdamagedplayer;

    float VX;
    float VY;

};