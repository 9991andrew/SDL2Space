#include "SinusoidalEnemy.h"
SinusoidalEnemy::SinusoidalEnemy(Spritesheet* spritesheet, float startX, float startY, float speed, float amplitude, float frequency, float ysp) :
    Enemy(spritesheet, startX, startY, speed),
    m_amplitude(amplitude),
    m_frequency(frequency),
    startyspeed(ysp){}
float direction = 1;
void SinusoidalEnemy::update(float deltaTime) {
    // Call the base class update function
   // Enemy::update(deltaTime);

    float newX = 0;
    float newY = 0;
    // Handle other updates like checking if out of bounds, etc.
    // Check if the enemy is at the left or right edge of the screen and reverse the horizontal direction
    if (m_dstRect.x <= 0 || (m_dstRect.x + m_dstRect.w) >= 320) {
        direction *= -1.0f;
    }
    std::cout << "direction? " << direction << std::endl;
    // Update the x position based on the fallSpeed and horizontal direction
    newX = (m_fallSpeed * deltaTime) * direction; // Adjust the constant value here to change the speed

    // Update the y position based on the sinusoidal function
    newY = m_amplitude * sin(m_frequency * (m_dstRect.x + newX)) * deltaTime + startyspeed * deltaTime;

    // Assign the updated x and y positions to the destination rectangle
    m_dstRect.x += static_cast<int>(newX);
    m_dstRect.y += static_cast<int>(newY);

}


void SinusoidalEnemy::draw(SDL_Renderer* renderer) {
	// Draw the enemy itself using the base class draw function
	Enemy::draw(renderer);

	

}