// Projectile.cpp
#include "Projectile.h"

Projectile::Projectile(Spritesheet* spritesheet, float x, float y, float speed)
    : m_spritesheet(spritesheet), m_speed(speed) {
    m_srcRect = { 0, 0, 8, 16 }; // Define the source rectangle for the projectile sprite.
    m_dstRect = { static_cast<int>(x), static_cast<int>(y), m_srcRect.w, m_srcRect.h };
}

void Projectile::update(float deltaTime) {
    m_dstRect.y -= static_cast<int>(m_speed * deltaTime);

    // Update other properties if necessary.
}

void Projectile::draw(SDL_Renderer* renderer) {
   
}

bool Projectile::isOffscreen() const {
    return m_dstRect.y + m_dstRect.h < 0;
}
