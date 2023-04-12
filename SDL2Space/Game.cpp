#include "Game.h"

;

Game::Game() : Window(nullptr), Renderer(nullptr), game(nullptr){

}
Game::~Game() {}

bool Game::Init() {
	
	// Initialize SDL_image
	 int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	 if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		 SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		 return false;
	 }
	if (!IMG_Init(flags)) {
		SDL_Log("Failed to initialize SDL2_image: %s", IMG_GetError());
		return false;
	}

	Window = SDL_CreateWindow("Cosmic Defenders", 100, 100, 320, 480, SDL_WINDOW_SHOWN);
	if (Window == nullptr) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Renderer == nullptr) {
		SDL_Log("Failed to create the renderer: %s", SDL_GetError());
		return false;
	}
	game = new MainGame;
	menu = new MainMenu(Renderer);
	SDL_Log("Renderer address in Game::Init(): %p", Renderer);
	game->Init(Renderer);
	gamestate = GameState::MainMenu;
	return true;
}
void Game::Cleanup() {
	if (game) {
		delete game;
		game = nullptr;
	}

	if (Renderer) {
		SDL_DestroyRenderer(Renderer);
		Renderer = nullptr;
	}

	if (Window) {
		SDL_DestroyWindow(Window);
		Window = nullptr;
	}

	IMG_Quit();
	SDL_Quit();
}

void Game::Run() {
	const int FPS = 60;
	const int FrameDelay = 1000 / FPS;
	Uint32 FrameStart;
	int FrameTime;

	while (true) {
		FrameStart = SDL_GetTicks();
		SDL_Event Event;

		while (SDL_PollEvent(&Event)) {

			switch (Event.type) {
			case SDL_QUIT:
				return;
			default:
				if (gamestate == GameState::MainMenu) {
					menu->handleInput(Event);
				}
				break;
			}
		}
		float deltatime = FrameDelay / 1000.0f;

		if(gamestate != GameState::MainMenu) {
			game->HandleInput(deltatime);
		}
		if (gamestate == GameState::MainMenu) {
			menu->update(deltatime);
		}
		else {

			game->Update(deltatime);
		}
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
		SDL_RenderClear(Renderer);

		if (gamestate == GameState::MainMenu) {
			menu->draw(Renderer);
		}
		else {
			game->Draw();
		}
	
		SDL_RenderPresent(Renderer);

		if (gamestate == GameState::MainMenu) {
			switch (menu->getSelectedButton()) {
			case MainMenu::Button::Play:
				gamestate = GameState::Play;
				break;
			case MainMenu::Button::Options:
				gamestate = GameState::Options;
				break;
			case MainMenu::Button::Exit:
			//	quit = true;
				exit(0);
				break;
			default:
				break;
			}
		}
		FrameTime = SDL_GetTicks() - FrameStart;
		if (FrameDelay > FrameTime) {
			SDL_Delay(FrameDelay - FrameTime);
		}

	}

}
