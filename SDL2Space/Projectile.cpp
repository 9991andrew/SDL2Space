// Projectile.cpp
#include "Projectile.h"

Projectile::Projectile(Spritesheet* spritesheet, float x, float y, float speed)
    : GameObject(x,y), m_spritesheet(spritesheet), m_animationTimer(0.0), m_animationSpeed(0.2f),m_currentframe(0), m_speed(speed) {
    m_srcRect = { 0, 0, 16,16}; // Define the source rectangle for the projectile sprite.
    m_dstRect = { static_cast<int>(x), static_cast<int>(y), m_srcRect.w, m_srcRect.h };
}

void Projectile::update(float deltaTime) {
    m_dstRect.y -= static_cast<int>(m_speed * deltaTime);

    m_animationTimer += deltaTime;

    if (m_animationTimer >= m_animationSpeed) {
        m_currentframe = (m_currentframe + 1) % m_spritesheet->gettotalframes();
        m_animationTimer = 0.0f;
    }
    // Update other properties if necessary.
    std::cout << "Projectile position: (" << m_dstRect.x << ", " << m_dstRect.y << ")\n";
    
}

void Projectile::draw(SDL_Renderer* renderer) {
    m_spritesheet->draw(renderer, m_dstRect.x, m_dstRect.y, 0);
}

bool Projectile::isOffscreen() const {
    return m_dstRect.y + m_dstRect.h < 0;
}
