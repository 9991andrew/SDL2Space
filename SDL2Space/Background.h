#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Background {
public:
    Background(SDL_Renderer* renderer, const char* filepath, int speed);
    ~Background();

    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);

private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    int m_speed;
    int m_position;
};

