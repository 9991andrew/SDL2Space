#include "Player.h"

Player::Player(Spritesheet* playerspritesheet, Spritesheet* projectilespritesheet, int startX, int startY) :
   GameObject(startX, startY), m_playerspritesheet(playerspritesheet),
    m_projectilespritesheet(projectilespritesheet),
    m_shootCooldown(0.0f), m_shootCooldownMax(0.5f),
    m_playercurrentframe(0), m_animationspeed(0.295f),
    m_animationtimer(0.0f) {}

void Player::handleInput(float deltaTime) {
    int speed = 300; // adjust as needed
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_LEFT]) {
        x -= speed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_RIGHT]) {
        x += speed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_UP]) {
        y -= speed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_DOWN]) {
        y += speed * deltaTime;
    }
    if (keyState[SDL_SCANCODE_SPACE]) {
        Shoot();
    }
}




void Player::update(float deltaTime) {
    m_animationtimer += deltaTime;
    if (m_animationtimer >= m_animationspeed) {
        m_playercurrentframe = (m_playercurrentframe + 1) % m_playerspritesheet->gettotalframes();
        m_animationtimer = 0.0f;
    }
    if (m_shootCooldown > 0) {
        m_shootCooldown -= deltaTime;
    }
    for (size_t i = 0; i < m_projectiles.size(); ++i) {
        m_projectiles[i]->update(deltaTime);

        if (m_projectiles[i]->isOffscreen()) {
            delete m_projectiles[i];
            m_projectiles.erase(m_projectiles.begin() + i);
            --i;
        }
    }

}

void Player::draw(SDL_Renderer* renderer) {
    m_playerspritesheet->draw(renderer, x, y, m_playercurrentframe);
}

void Player::Shoot() {
    if (m_shootCooldown <= 0.0f) {
        
        float projectilespeed = 175.0f;
        Projectile* projectile = new Projectile(m_projectilespritesheet, x,y, projectilespeed );
        m_projectiles.push_back(projectile);
        m_shootCooldown = m_shootCooldownMax;

    }
}