#include "MainGame.h"
#include "ShootingEnemy.h"

#include <ctime>
#include <cstdlib>
#include <algorithm>
MainGame::MainGame() : m_renderer(nullptr), playerspritesheet(nullptr), projectilespritesheet(nullptr),
					   player(nullptr), background(nullptr), enemyspawninterval(0.0f), enemyspawntimer(0.0f),
					   enemyspritesheet(nullptr), mediumenemyspritesheet(nullptr), bigenemyspritesheet(nullptr), 
	                   explosionspritesheet(nullptr), m_font(nullptr), m_score(0) {
	SDL_Log("Renderer address in MainGame constructor: %p", m_renderer);

	m_textColor = { 255,255,255 };
	m_scoreSurface = nullptr;
	m_scoreTexture = nullptr;
	m_scoreRect = { 0,0,0 };

	m_score = 0;
	srand(static_cast<unsigned>(time(nullptr))); // Seed generator
}

MainGame::~MainGame() {	
	TTF_CloseFont(m_font);
	TTF_Quit();
	SDL_FreeSurface(m_scoreSurface);
	SDL_DestroyTexture(m_scoreTexture);
}

bool MainGame::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
	// Check for intersection between rectangles
	SDL_Rect Result;
	return SDL_IntersectRect(&a,&b,&Result);
}

void MainGame::removeSinEnemy(SinusoidalEnemy* enemy) {
	auto it = std::find_if(enemyobjects.begin(), enemyobjects.end(), [enemy](const std::shared_ptr<Enemy>& ptr) {
		return ptr.get() == enemy;
		});
}


void MainGame::Init(SDL_Renderer* renderer) {
	m_renderer = renderer;
	TTF_Init();
	m_font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf",16);
	SDL_Log("Renderer address in MainGame::Init(): %p", m_renderer);
	const char* enemyfilepath = "enemy-small.png";
	const char* enemymediumfilepath = "enemy-medium.png";
	const char* enemybigfilepath = "enemy-big.png";
	const char* playerfilepath = "ship.png";
	const char* projectilefilepath = "projectiles.png";
	const char* explosionfilepath = "explosion.png";
	enemyspritesheet = std::make_shared<Spritesheet>(m_renderer, enemyfilepath, 16, 16);
	mediumenemyspritesheet = std::make_shared<Spritesheet>(m_renderer, enemymediumfilepath, 32,16);
	bigenemyspritesheet = std::make_shared<Spritesheet>(m_renderer, enemybigfilepath, 32,32);
	playerspritesheet = std::make_shared<Spritesheet>(m_renderer, playerfilepath, 16, 24);
	projectilespritesheet = std::make_shared<Spritesheet>(m_renderer, projectilefilepath, 16, 16);
	explosionspritesheet = std::make_shared<Spritesheet>(m_renderer, explosionfilepath, 16, 16);
	background = std::make_unique<Background>(m_renderer, "background.png", 100);
	player = std::make_unique<Player>(playerspritesheet, projectilespritesheet, 320/2, 400);
	enemyspawntimer = 0.0f;
	enemyspawninterval = 2.0f;

	UpdateScoreTexture();
}


void MainGame::SpawnEnemy() {
	

	float x, y;
	std::shared_ptr<Enemy> enemy = nullptr;
	switch (rand() % 4) {
	case 0:
		x = rand() % 275;
		y = 0;
		enemy = std::make_shared<SinusoidalEnemy>(bigenemyspritesheet, projectilespritesheet, x, y, 100.0f + rand() % 50, 5 + rand() % 10, 15, 75.0f);

		break;
	case 1:
		x = rand() % 275;
		y = 0;
		enemy = std::make_shared <ShootingEnemy>(mediumenemyspritesheet, x, y, 150.0f, projectilespritesheet, 0.5 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
		break;
	case 2:
		x = rand() % 275;
		y = 0;
		enemy = std::make_shared<ShootingEnemy>(mediumenemyspritesheet, x, y, 100.0f, projectilespritesheet, 0.5 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
		break;
	case 3:
		x = rand() % 275;
		y = 0;
		enemy = std::make_shared<Enemy>(enemyspritesheet, x, y, 235.0f);
		break;
	}
	if (enemy) enemyobjects.push_back(std::move(enemy));
	spawnsequence++;
}



void MainGame::HandleInput(float deltatime) {
	player->handleInput(deltatime);
}

void MainGame::Update(float deltaTime) {
	background->update(deltaTime);
	player->update(deltaTime);
	for (const auto& projectile : player->getProjectiles()) {
		projectile->update(deltaTime);
	}
	//Remove the bullets that are off the screen.

	for (const auto& enemy : enemyobjects) {
		ShootingEnemy* shootingEnemy = dynamic_cast<ShootingEnemy*>(enemy.get());

		if (shootingEnemy) {
			for (auto it = shootingEnemy->getBullets().begin(); it != shootingEnemy->getBullets().end();) {
				Projectile* projectile = (*it).get();
				if (projectile->isOffscreen()) {
					shootingEnemy->getBullets().erase(it);

				}
				else {
					++it;
				}
			}
		}
	}

	//Update the spawn timer
	enemyspawntimer += deltaTime;
	//Spawn an enemy when the timer reaches the spawn interval
	if (enemyspawntimer >= enemyspawninterval) {
		SpawnEnemy();
		//Reset the timer after we have spawned one.
		enemyspawntimer = 0.0f;
	}
	// Update enemy objects
	for (const auto& enemy : enemyobjects) {
		enemy->update(deltaTime);
		std::shared_ptr<ShootingEnemy> shootingEnemy = std::dynamic_pointer_cast<ShootingEnemy>(enemy);
		if (shootingEnemy) {
			auto& bullets = shootingEnemy->getBullets();
			for (auto it = bullets.begin(); it != bullets.end();) {
				Projectile* projectile = (*it).get();
				if (!projectile->GetHasDamagedPlayer()) {
					bool collision = CheckCollision(projectile->GetDstRect(), player->GetDstRect());
					if (collision) {
						player->TakeDamage(10);
						std::cout << "Player Health: " << player->GetPlayerHealth() << std::endl;
						projectile->SetHasDamagedPlayer(true);
						it = bullets.erase(it);
					}
					else {
						projectile->SetHasDamagedPlayer(false);
						++it;
					}
				}
				else {
					++it;

				}
			}
		}
		std::shared_ptr<SinusoidalEnemy> sinusoidalEnemy = std::dynamic_pointer_cast<SinusoidalEnemy>(enemy);
		if (sinusoidalEnemy) {
			auto& bullets = sinusoidalEnemy->GetProjectiles();
			for (auto it = bullets.begin(); it != bullets.end();) {
				Projectile* projectile = (*it).get();
				if (!projectile->GetHasDamagedPlayer()) {
					bool collision = CheckCollision(projectile->GetDstRect(), player->GetDstRect());
					if (collision) {
						player->TakeDamage(10);
						std::cout << "Player Health: " << player->GetPlayerHealth() << std::endl;
						projectile->SetHasDamagedPlayer(true);			
						it = bullets.erase(it);
					}
					else {
						++it;
					}
				}
				else {
					++it;
				}
			}
		
		}
		
	}

			



		//Loop through all projectiles and enemies. Creating a projectilehit boolean for each projectile.
		for (auto projectileIter = player->getProjectiles().begin();
			projectileIter != player->getProjectiles().end();) {
			bool projectileHit = false;
			for (auto enemyIter = enemyobjects.begin();
				enemyIter != enemyobjects.end();) {
				//Enemy hit happens here.
				std::cout << "Hit! " << CheckCollision((*projectileIter)->GetDstRect(), (*enemyIter)->GetDstRect()) << std::endl;
				if (CheckCollision((*projectileIter)->GetDstRect(), (*enemyIter)->GetDstRect())) {
					//On collision.
					m_score += 100;
					
					UpdateScoreTexture();
					std::unique_ptr<Explosion> explosion = std::make_unique<Explosion>
					(explosionspritesheet,
						(*enemyIter)->GetDstRect().x,
						(*enemyIter)->GetDstRect().y,
						0.05f);

					gameobjects.push_back(std::move(explosion));
					std::shared_ptr<GameObject> enemy = *enemyIter;
					(*enemyIter) = nullptr;
					enemyIter = enemyobjects.erase(enemyIter);
					projectileIter = player->getProjectiles().erase(projectileIter);
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
	for (auto explosionIter = gameobjects.begin(); explosionIter != gameobjects.end();) {
		(*explosionIter)->update(deltaTime);
		
		Explosion* explosion = dynamic_cast<Explosion*>((*explosionIter).get());

		if (explosion->isAnimationFinished()) {
			explosionIter = gameobjects.erase(explosionIter);
		}
		else {
			++explosionIter;
		}
	}

}


void MainGame::UpdateScoreTexture() {
	if (m_scoreSurface) {
		SDL_FreeSurface(m_scoreSurface);
	}
	if (m_scoreTexture) {
		SDL_DestroyTexture(m_scoreTexture);
	}
	//...

	//This will start off as a really small rectangle because there is no text in the rectangle.
	m_scoreSurface = TTF_RenderText_Solid(m_font, std::to_string(m_score).c_str(), m_textColor);
	int minWidth = 100;  // Set a minimum width for the black rectangle
	int rectWidth = std::max(m_scoreSurface->w, minWidth);
	m_scoreRect = { 320 / 2 - rectWidth / 2, 10, rectWidth, m_scoreSurface->h };
	m_scoreTexture = SDL_CreateTextureFromSurface(m_renderer, m_scoreSurface);
	m_scoreRect = { 320 / 2 - m_scoreSurface->w / 2, 10, m_scoreSurface->w, m_scoreSurface->h };
}


void MainGame::Draw() {

	background->draw(m_renderer);
	player->draw(m_renderer);



	

	for (const auto& projectile : player->getProjectiles()) {
		projectile->draw(m_renderer);
	}
	//Draw the enemies
	for (const auto& enemy : enemyobjects) {
		Enemy* theenemy = dynamic_cast<Enemy*>(enemy.get());
		enemy->draw(m_renderer);
	}
	// Draw explosion animations
	for (const auto& explosion : gameobjects) {
		Explosion* theexplosion = dynamic_cast<Explosion*>(explosion.get());
		theexplosion->draw(m_renderer);
	}

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_Rect blackRect = { m_scoreRect.x - 10, m_scoreRect.y - 5, m_scoreRect.w + 20, m_scoreRect.h + 10 };
	SDL_RenderFillRect(m_renderer, &blackRect);
	SDL_RenderCopy(m_renderer, m_scoreTexture, nullptr, &m_scoreRect);
	
}

