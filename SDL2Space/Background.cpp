#include "Background.h"
Background::Background(SDL_Renderer* renderer, const char* filepath, int speed)
    : m_renderer(renderer), m_speed(speed), m_position(0) {
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
Background::~Background() {
    SDL_DestroyTexture(m_texture);
}

void Background::update(float deltaTime) {
    m_position -= static_cast<int>(m_speed * deltaTime) % 640;
    if (m_position < -480) {
        m_position = 0;
    }
}

void Background::draw(SDL_Renderer* renderer) {
    SDL_Rect destRect1 = { 0, m_position, 640, 480 };
    SDL_Rect destRect2 = { 0, m_position + 480 , 640, 480 };

    SDL_RenderCopy(renderer, m_texture, nullptr, &destRect1);
    SDL_RenderCopy(renderer, m_texture, nullptr, &destRect2);
}