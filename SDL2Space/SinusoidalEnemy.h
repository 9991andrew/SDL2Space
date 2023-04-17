#pragma once
#include "Enemy.h"
#include "Projectile.h"
#include <vector>
class SinusoidalEnemy : public Enemy {
public:
    ~SinusoidalEnemy();
    SinusoidalEnemy(std::shared_ptr<Spritesheet> spritesheet,
        std::shared_ptr<Spritesheet> projectilespritesheet,
        float startX, 
        float startY,
        float speed, 
        float amplitude, 
        float frequency,
        float yspeed
       );
    std::vector<std::shared_ptr<Projectile>>& GetProjectiles() { return projectiles; }
    void update(float deltaTime) override;
    void draw(SDL_Renderer*) override;
private:
    float m_amplitude;
    float m_frequency;
    float startyspeed;
    float explosiontimer;
    std::shared_ptr<Spritesheet> projectilespritesheet;
    std::vector<std::shared_ptr<Projectile>> projectiles;
};