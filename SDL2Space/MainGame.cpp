#include "MainGame.h"

MainGame::MainGame() : m_renderer(nullptr), playerspritesheet(nullptr), projectilespritesheet(nullptr), player(nullptr), background(nullptr) {
	SDL_Log("Renderer address in MainGame constructor: %p", m_renderer);
}

MainGame::~MainGame() {
	delete player;
	delete playerspritesheet;
}

void MainGame::Init(SDL_Renderer* renderer) {
	m_renderer = renderer;
	SDL_Log("Renderer address in MainGame::Init(): %p", m_renderer);
	const char* playerfilepath = "ship.png";
	const char* projectilefilepath = "projectiles.png";
	playerspritesheet = new Spritesheet(m_renderer, playerfilepath, 16, 24);
	projectilespritesheet = new Spritesheet(m_renderer, projectilefilepath, 16, 16);
	background = new Background(m_renderer, "background.png", 100);
	player = new Player(playerspritesheet, projectilespritesheet, 640/2, 400);
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
}

void MainGame::Draw() {
	background->draw(m_renderer);
	player->draw(m_renderer);
	for (Projectile* projectile : player->getProjectiles()) {
		projectile->draw(m_renderer);
	}
}