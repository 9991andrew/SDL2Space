#include "SinusoidalEnemy.h"

SinusoidalEnemy::SinusoidalEnemy(std::shared_ptr<Spritesheet> spritesheet,
    std::shared_ptr<Spritesheet> projectilespritesheet, 
    float startX,
    float startY,
    float speed,
    float amplitude, 
    float frequency, 
    float ysp
    )
    :
    Enemy(spritesheet, startX, startY, speed),
    m_amplitude(amplitude),
    m_frequency(frequency),
    startyspeed(ysp),
    projectilespritesheet(projectilespritesheet)
   {

    explosiontimer = static_cast<float>(rand() % 5 + 2);
}

SinusoidalEnemy::~SinusoidalEnemy() {
}

float direction = 1.0f;
void SinusoidalEnemy::update(float deltaTime) {
    // Call the base class update function
    Enemy::update(deltaTime);
    explosiontimer -= deltaTime;
    if (!isMarkedForDel() && explosiontimer <= 0) {
        
        int numbullets = 8;
        for (int i = 0; i < numbullets; i++) {
            float angle = static_cast<float>(i) / numbullets * 2.0f * M_PI;
            float bulletSpeed = 150.0f; // Adjust bullet speed as needed
            float vx = cos(angle) * bulletSpeed;
            float vy = sin(angle) * bulletSpeed;
            std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(projectilespritesheet, m_dstRect.x, m_dstRect.y, vx, vy);
            projectiles.push_back(std::move(projectile));
        }
        explosiontimer = static_cast<float>(rand() % 5 + 2);
        this->setMarkedForDel(true);
    }
   
    for (const auto& projectile : projectiles) {
        projectile->update(deltaTime);

    }

    float newX = 0;
    float newY = 0;
    // Handle other updates like checking if out of bounds, etc.
    // Check if the enemy is at the left or right edge of the screen and reverse the horizontal direction
    if (m_dstRect.x <= 0 || (m_dstRect.x + m_dstRect.w) >= 320) {
        direction *= -1.0f;
    }
    // Update the x position based on the fallSpeed and horizontal direction
    newX = (m_fallSpeed * deltaTime) * direction; // Adjust the constant value here to change the speed

    // Update the y position based on the sinusoidal function
    newY = m_amplitude * sin(m_frequency * (m_dstRect.x )) * deltaTime;

    // Assign the updated x and y positions to the destination rectangle
    m_dstRect.x += static_cast<int>(newX);
    m_dstRect.y += static_cast<int>(newY);

}


void SinusoidalEnemy::draw(SDL_Renderer* renderer) {
    // Draw the enemy itself using the base class draw function
    Enemy::draw(renderer);

    for (const auto& projectile : projectiles) {
        projectile->draw(renderer);
    }

	

}