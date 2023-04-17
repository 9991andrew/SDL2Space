#pragma once
#include "Enemy.h"
#include "Projectile.h"
#include <vector>
class ShootingEnemy : public Enemy
{
public:
	ShootingEnemy
	(
		std::shared_ptr<Spritesheet> spritesheet,
		float startX, 
		float startY, 
		float speed,
		std::shared_ptr<Spritesheet> bulletspritesheet,
		float shootinterval
	);

	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;
	std::vector<std::shared_ptr<Projectile>>& getBullets() { return projectiles; }


private:
	void ShootProjectile();
	std::shared_ptr<Spritesheet> bulletspritesheet;
	float shoottimer;
	float shootinterval;
	std::vector<std::shared_ptr<Projectile>> projectiles;

};

