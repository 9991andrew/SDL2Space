#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy
(
	std::shared_ptr<Spritesheet> spritesheet,
	float startX,
	float startY, 
	float speed, 
	std::shared_ptr<Spritesheet> bulletSpritesheet,
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

		if ((*projectileIter)->isOffscreen() ) {
			projectileIter = projectiles.erase(projectileIter);
		}
		else {
			++projectileIter;
		}

	}
}


void ShootingEnemy::ShootProjectile() {
	// Calculate the bullet's position and direction
	

	// Create a new bullet and add it to the bullets vector
	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(bulletspritesheet, x, m_dstRect.y, 0, 200);
	projectiles.push_back(std::move(projectile));
}

void ShootingEnemy::draw(SDL_Renderer* renderer) {
	// Draw the enemy itself using the base class draw function
	Enemy::draw(renderer);

	// Draw the projectiles fired by the enemy
	for (const auto& projectile : projectiles) {
		projectile->draw(renderer);
	}

}