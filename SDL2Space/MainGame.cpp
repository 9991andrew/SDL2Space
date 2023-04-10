#include "MainGame.h"

MainGame::MainGame() : m_renderer(nullptr), spritesheet(nullptr), player(nullptr), background(nullptr) {
	SDL_Log("Renderer address in MainGame constructor: %p", m_renderer);
}

MainGame::~MainGame() {
	delete player;
	delete spritesheet;
}

void MainGame::Init(SDL_Renderer* renderer) {
	m_renderer = renderer;
	SDL_Log("Renderer address in MainGame::Init(): %p", m_renderer);
	const char* filepath = "ship.png";
	
	spritesheet = new Spritesheet(m_renderer, filepath, 16, 24);
	player = new Player(spritesheet, 640/2, 400);
	background = new Background(m_renderer, "background.png", 100);
}

void MainGame::HandleInput(SDL_Event event) {
	player->handleInput(event);
}

void MainGame::Update(float deltaTime) {
	background->update(deltaTime);
	player->update(deltaTime);

}

void MainGame::Draw() {
	background->draw(m_renderer);
	player->draw(m_renderer);
}