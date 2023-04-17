#include "Player.h"

Player::Player(std::shared_ptr<Spritesheet> playerspritesheet, std::shared_ptr<Spritesheet> projectilespritesheet, int startX, int startY) :
    GameObject(startX, startY), m_playerspritesheet(playerspritesheet),
    m_projectilespritesheet(projectilespritesheet),
    m_shootCooldown(0.0f), m_shootCooldownMax(0.5f),
    m_playercurrentframe(0), m_animationspeed(0.295f),
    m_animationtimer(0.0f) {

    m_dstRect = { startX, startY, playerspritesheet->GetWidth(), playerspritesheet->GetHeight() };

    playerhealth = 100;
    maxplayerhealth = 100;
    healthbarrect = { 10, 470, (int)(300 * ((float)playerhealth / (float)maxplayerhealth)), 20 };
    healthbarbackground = { 10, 470, 300, 20 };
}

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
    m_dstRect.x = x;
    m_dstRect.y = y;
}


void Player::TakeDamage(int damage) {
    if (playerhealth < 0) {
        playerhealth = 0;
    }
        playerhealth -= damage;
  

        healthbarrect.w = (int)(300 * ((float)playerhealth / (float)maxplayerhealth));

    
}

void Player::update(float deltaTime) {
    m_animationtimer += deltaTime;
    // Handle other updates like checking if out of bounds, etc.
// Check if the enemy is at the left or right edge of the screen and reverse the horizontal direction

    
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
            m_projectiles.erase(m_projectiles.begin() + i);
            --i;
        }
    }

    if (x < 0) {
        std::cout << "Collision: x < 0" << std::endl;
        x = 0;
    }

    if ((x + m_dstRect.w) >= 321) {
        std::cout << "Collision: > 320" << std::endl;
        x = 320 - m_dstRect.w;
    }

}

void Player::DrawHealthBarRect(SDL_Renderer* renderer) {
    //Background.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &healthbarbackground);
    //Actual life bar.
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &healthbarrect);

}

void Player::draw(SDL_Renderer* renderer) {
    m_playerspritesheet->draw(renderer, x, y, m_playercurrentframe);
    DrawHealthBarRect(renderer);
}

void Player::Shoot() {
    if (m_shootCooldown <= 0.0f) {

        float projectilespeed = -175.0f;
        std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(m_projectilespritesheet, x, y, 0, projectilespeed);
        m_projectiles.push_back(std::move(projectile));
        std::cout << "Hi" << m_projectiles.size()<<std::endl;
        m_shootCooldown = m_shootCooldownMax;

    }
}