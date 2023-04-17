#include "Enemy.h"
Enemy::Enemy(std::shared_ptr<Spritesheet> spritesheet, int startX, int startY, float speed) :
    GameObject(startX, startY),
    m_spritesheet(spritesheet),
    m_fallSpeed(speed),
    m_currentframe(0),
    m_animationspeed(0.295f),
    m_animationtimer(0.0f),
    m_isactive(true){
    
    m_dstRect = 
    {
        startX, 
        startY, 
        m_spritesheet->GetWidth(),
        m_spritesheet->GetHeight()
    };

}


void Enemy::update(float deltaTime) {

    m_animationtimer += deltaTime;
    if (m_animationtimer >= m_animationspeed) {
        m_currentframe = (m_currentframe + 1) % m_spritesheet->gettotalframes();
        m_animationtimer = 0.0f;
    }
    m_dstRect.y += static_cast<int>(m_fallSpeed * deltaTime);
    //If it hits the end of the screen (goes out of bounds).
    if (m_dstRect.y > m_spritesheet->GetHeight()) {
        m_isactive = false;
    }
}
void Enemy::draw(SDL_Renderer* renderer) {
    m_spritesheet->draw(renderer, m_dstRect.x, m_dstRect.y, m_currentframe);
}

