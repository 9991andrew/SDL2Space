#pragma once

#include <SDL.h>
#include "Player.h"
#include "Spritesheet.h"
#include "Background.h"

class MainGame {
public:
    MainGame();
    ~MainGame();

    void Init(SDL_Renderer* renderer);
    void HandleInput(SDL_Event event);
    void Update(float deltaTime);
    void Draw();
    void Cleanup();

private:
    SDL_Renderer* m_renderer;
    Spritesheet* spritesheet;
    Player* player;
    Background* background;
};
