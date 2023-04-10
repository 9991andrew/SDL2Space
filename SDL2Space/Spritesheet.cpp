
    
#include "Spritesheet.h"

Spritesheet::Spritesheet(SDL_Renderer* renderer, const char* filepath, int spriteWidth, int spriteHeight) :
    renderer(renderer), m_texture(nullptr), m_spriteWidth(spriteWidth), m_spriteHeight(spriteHeight) {

    if (renderer == nullptr) {
        SDL_Log("Renderer is not properly initialized");
        return;
    }

    SDL_Surface* surface = IMG_Load(filepath);

    if (surface == nullptr) {
        SDL_Log("Failed to load image: %s", SDL_GetError());
        return;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (m_texture == nullptr) {
        SDL_Log("Failed to create texture: %s", IMG_GetError());
        return;
    }

    SDL_FreeSurface(surface);
}

Spritesheet::~Spritesheet() {
    SDL_DestroyTexture(m_texture);
}

void Spritesheet::draw(SDL_Renderer* renderer, int x, int y, int spriteIndex) {
    int numColumns, numRows;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &numColumns, &numRows);
    numColumns /= m_spriteWidth;
    numRows /= m_spriteHeight;

    int row = spriteIndex / numColumns;
    int col = spriteIndex % numColumns;

    SDL_Rect srcRect = { col * m_spriteWidth, row * m_spriteHeight, m_spriteWidth, m_spriteHeight };
    SDL_Rect destRect = { x, y, m_spriteWidth, m_spriteHeight };

    SDL_RenderCopy(renderer, m_texture, &srcRect, &destRect);
}

int Spritesheet::gettotalframes() const {
    int numcolumns, numrows;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &numcolumns, &numrows);
    
    numcolumns /= m_spriteWidth;
    numrows /= m_spriteHeight;
    return numcolumns * numrows;
}