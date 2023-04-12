#include "MainGame.h"
#include "ShootingEnemy.h"
#include "SinusoidalEnemy.h"

#include <ctime>
#include <cstdlib>
MainGame::MainGame() : m_renderer(nullptr), playerspritesheet(nullptr), projectilespritesheet(nullptr),
					   player(nullptr), background(nullptr), enemyspawninterval(0.0f), enemyspawntimer(0.0f),
					   enemyspritesheet(nullptr), mediumenemyspritesheet(nullptr), bigenemyspritesheet(nullptr), 
						explosionspritesheet(nullptr) {
	SDL_Log("Renderer address in MainGame constructor: %p", m_renderer);
}

MainGame::~MainGame() {
	delete player;
	delete playerspritesheet;

	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	for (Explosion* explosion : explosions) {
		delete explosion;
	}
	delete enemyspritesheet;
	delete explosionspritesheet;
}

bool MainGame::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
	// Check for intersection between rectangles
	return 
		(a.x < b.x + b.w) && 
		(a.x + a.w > b.x) &&
		(a.y < b.y + b.h) && 
		(a.y + a.h > b.y);
}


void MainGame::Init(SDL_Renderer* renderer) {
	m_renderer = renderer;
	SDL_Log("Renderer address in MainGame::Init(): %p", m_renderer);
	const char* enemyfilepath = "enemy-small.png";
	const char* enemymediumfilepath = "enemy-medium.png";
	const char* enemybigfilepath = "enemy-big.png";
	const char* playerfilepath = "ship.png";
	const char* projectilefilepath = "projectiles.png";
	const char* explosionfilepath = "explosion.png";
	enemyspritesheet = new Spritesheet(m_renderer, enemyfilepath, 16,16);
	mediumenemyspritesheet = new Spritesheet(m_renderer, enemymediumfilepath, 32,16);
	bigenemyspritesheet = new Spritesheet(m_renderer, enemybigfilepath, 32,32);
	playerspritesheet = new Spritesheet(m_renderer, playerfilepath, 16, 24);
	projectilespritesheet = new Spritesheet(m_renderer, projectilefilepath, 16, 16);
	explosionspritesheet = new Spritesheet(m_renderer, explosionfilepath, 16, 16);
	background = new Background(m_renderer, "background.png", 100);
	player = new Player(playerspritesheet, projectilespritesheet, 320/2, 400);
	enemyspawntimer = 0.0f;
	enemyspawninterval = 2.0f;
}

void MainGame::SpawnEnemy() {
	srand(static_cast<unsigned>(time(nullptr))); // Seed generator

	float x, y;
	Enemy* enemy = nullptr;
	switch (rand() % 4) {
	case 0:
		x = rand() % 275;
		y = 0;
		enemy = new SinusoidalEnemy(bigenemyspritesheet, x, y, 100.0f + rand() % 50, 5 + rand() % 10, 15, 75.0f);
		break;
	case 1:
		x = rand() % 275;
		y = 0;
		enemy = new ShootingEnemy(mediumenemyspritesheet, x, y, 150.0f, projectilespritesheet, 0.5 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
		break;
	case 2:
		x = rand() % 275;
		y = 0;
		enemy = new ShootingEnemy(mediumenemyspritesheet, x, y, 100.0f, projectilespritesheet, 0.5 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
		break;
	case 3:
		x = rand() % 275;
		y = 0;
		enemy = new Enemy(enemyspritesheet, x, y, 235.0f);
		break;
	}
	if (enemy) enemies.push_back(enemy);
	spawnsequence++;
}

void MainGame::HandleInput(float deltatime) {
	player->handleInput(deltatime);
}

void MainGame::Update(float deltaTime) {
	background->update(deltaTime);
	player->update(deltaTime);
	for (Projectile* projectile : player->getProjectiles()) {
		projectile->update(deltaTime);
	}
	//Update the spawn timer
	enemyspawntimer += deltaTime;
	//Spawn an enemy when the timer reaches the spawn interval
	if (enemyspawntimer >= enemyspawninterval) {
		SpawnEnemy();
		//Reset the timer after we have spawned one.
		enemyspawntimer = 0.0f;
	}
	for (Enemy* enemy : enemies) {
		enemy->update(deltaTime);
	}
	//Loop through all projectiles and enemies. Creating a projectilehit boolean for each projectile.
	for (auto projectileIter = player->getProjectiles().begin();
		projectileIter != player->getProjectiles().end();) {
		bool projectileHit = false;
		for (auto enemyIter = enemies.begin();
			enemyIter != enemies.end();) {
			if (CheckCollision((*projectileIter)->GetDstRect(), (*enemyIter)->GetDstRect())) {
				//On collision.
				Explosion* explosion = new Explosion
					(explosionspritesheet,
					(*enemyIter)->GetDstRect().x,
					(*enemyIter)->GetDstRect().y,
					0.05f);

				explosions.push_back(explosion);
				delete* projectileIter;

				projectileIter = player->getProjectiles().erase(projectileIter);
				delete* enemyIter;

				enemyIter = enemies.erase(enemyIter);
				projectileHit = true;
				break;
			}
			else {
				++enemyIter;
			}
		}
		if (!projectileHit) {
			++projectileIter;	
		}
	}

	// Update explosion animations
	for (auto explosionIter = explosions.begin(); explosionIter != explosions.end();) {
		(*explosionIter)->update(deltaTime);

		if ((*explosionIter)->isAnimationFinished()) {
			delete* explosionIter;
			explosionIter = explosions.erase(explosionIter);
		}
		else {
			++explosionIter;
		}
	}


}

void MainGame::Draw() {
	background->draw(m_renderer);
	player->draw(m_renderer);
	for (Projectile* projectile : player->getProjectiles()) {
		projectile->draw(m_renderer);
	}
	//Draw the enemies
	for (Enemy* enemy : enemies) {
		enemy->draw(m_renderer);
	}
	// Draw explosion animations
	for (Explosion* explosion : explosions) {
		explosion->draw(m_renderer);
	}
	
}