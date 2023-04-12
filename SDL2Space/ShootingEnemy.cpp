#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy
(
	Spritesheet* spritesheet,
	float startX,
	float startY, 
	float speed, 
	Spritesheet* bulletSpritesheet,
	float shootInterval
):Enemy(spritesheet, startX, startY,speed), 
	bulletspritesheet(bulletSpritesheet), 
	shoottimer(0),
	shootinterval(shootInterval) {}

void ShootingEnemy::update(float deltaTime) {
	Enemy::update(deltaTime);

	shoottimer += deltaTime;

	if (shoottimer >= shootinterval) {
		ShootProjectile();
		shoottimer = 0.0f;
	}

	for (auto projectileIter = projectiles.begin(); projectileIter != projectiles.end();) {
		(*projectileIter)->update(deltaTime);

		if ((*projectileIter)->isOffscreen()) {
			delete* projectileIter;
			projectileIter = projectiles.erase(projectileIter);
		}
		else {
			++projectileIter;
		}

	}
}


void ShootingEnemy::ShootProjectile() {
	// Calculate the bullet's position and direction
	
	std::cout << "Shooting projectile" << std::endl;

	// Create a new bullet and add it to the bullets vector
	Projectile* projectile = new Projectile(bulletspritesheet, x, m_dstRect.y, -200);
	projectiles.push_back(projectile);
}

void ShootingEnemy::draw(SDL_Renderer* renderer) {
	// Draw the enemy itself using the base class draw function
	Enemy::draw(renderer);

	// Draw the projectiles fired by the enemy
	for (Projectile* projectile : projectiles) {
		projectile->draw(renderer);
	}

}