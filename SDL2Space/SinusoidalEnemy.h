#pragma once
#include "Enemy.h"
class SinusoidalEnemy : public Enemy {
public:
    SinusoidalEnemy(Spritesheet* spritesheet, float startX, float startY, float speed, float amplitude, float frequency, float yspeed);

    void update(float deltaTime) override;
    void draw(SDL_Renderer*) override;
    
private:
    float m_amplitude;
    float m_frequency;
    float startyspeed;
};