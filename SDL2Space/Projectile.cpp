// Projectile.cpp
#include "Projectile.h"

Projectile::Projectile(std::shared_ptr<Spritesheet> spritesheet, float x, float y, float vx, float vy)
    : GameObject(x,y),hasdamagedplayer(false), m_spritesheet(spritesheet), VX(vx), VY(vy), m_animationTimer(0.0), m_animationSpeed(0.2f),m_currentframe(0) {
    m_srcRect = { 0, 0, 16,16}; // Define the source rectangle for the projectile sprite.
    m_dstRect = { static_cast<int>(x), static_cast<int>(y), m_srcRect.w, m_srcRect.h };
}

Projectile::~Projectile() {
   
}

void Projectile::update(float deltaTime) {
    m_dstRect.x += VX * deltaTime;
    m_dstRect.y += VY * deltaTime;

    m_animationTimer += deltaTime;

    if (m_animationTimer >= m_animationSpeed) {
        m_currentframe = (m_currentframe + 1) % m_spritesheet->gettotalframes();
        m_animationTimer = 0.0f;
    }
    // Update other properties if necessary.

    
}

void Projectile::draw(SDL_Renderer* renderer) {
    m_spritesheet->draw(renderer, m_dstRect.x, m_dstRect.y, 0);
}

bool Projectile::isOffscreen() const {
    return (m_dstRect.y + m_dstRect.h < 0) || (m_dstRect.y > 480);
}
