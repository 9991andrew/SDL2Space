#pragma once
#include "Enemy.h"
#include "Projectile.h"
#include <vector>
class ShootingEnemy : public Enemy
{
public:
	ShootingEnemy
	(
		Spritesheet* spritesheet,
		float startX, 
		float startY, 
		float speed,
		Spritesheet* bulletspritesheet, 
		float shootinterval
	);

	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;
	std::vector<Projectile*>& getBullets() { return projectiles; }

private:
	void ShootProjectile();
	Spritesheet* bulletspritesheet;
	float shoottimer;
	float shootinterval;
	std::vector<Projectile*> projectiles;
};

