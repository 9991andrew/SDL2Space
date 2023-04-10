#pragma once

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Spritesheet {
public:
    Spritesheet(SDL_Renderer* renderer, const char* filepath, int spriteWidth, int spriteHeight);
    ~Spritesheet();

    void draw(SDL_Renderer* renderer, int x, int y, int spriteIndex);
    int gettotalframes() const;

private:
    SDL_Texture* m_texture;
    SDL_Renderer* renderer;
    int m_spriteWidth;
    int m_spriteHeight;
};
