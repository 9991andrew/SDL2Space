#pragma once

#include <SDL.h>
#include "MainGame.h"
#include "MainMenu.h"
class Game {

public:
    enum class GameState {
        MainMenu,
        Play,
        Options,
        Exit
    };
    Game();
    ~Game();
    bool Init();
    void Cleanup();
    void Run();

private:
    SDL_Renderer* Renderer;
    SDL_Window* Window;
    MainGame* game;
    MainMenu* menu;
    GameState gamestate;
};
