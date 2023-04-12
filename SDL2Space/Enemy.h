#pragma once
#include "GameObject.h"
#include "Spritesheet.h"
class Enemy : public GameObject {
public:

    Enemy(Spritesheet* spritesheet, int startX, int startY, float speed);
     virtual void update(float deltaTime) override;
    virtual void draw(SDL_Renderer* renderer) override;
//    bool hasCollided(const GameObject& other) const;
    SDL_Rect& GetDstRect();

protected:
    Spritesheet* m_spritesheet;
    int m_currentframe;
    bool m_isactive;
    float m_animationspeed;
    float m_animationtimer;
    float m_fallSpeed;
};


