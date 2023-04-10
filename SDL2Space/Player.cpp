#include "Player.h"

Player::Player(Spritesheet* spritesheet, int startX, int startY) :
    m_spritesheet(spritesheet), m_x(startX), m_y(startY), m_currentframe(0), m_animationspeed(0.295f), m_animationtimer(0.0f) {}

void Player::handleInput(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            m_x -= 5;
            break;
        case SDLK_RIGHT:
            m_x += 5;
            break;
        case SDLK_UP:
            m_y -= 5;
            break;
        case SDLK_DOWN:
            m_y += 5;
            break;
        default:
            break;
        }
    }
}

void Player::update(float deltaTime) {
    m_animationtimer += deltaTime;
    if (m_animationtimer >= m_animationspeed) {
        m_currentframe = (m_currentframe + 1) % m_spritesheet->gettotalframes();
        m_animationtimer = 0.0f;
    }
}

void Player::draw(SDL_Renderer* renderer) {
    m_spritesheet->draw(renderer, m_x, m_y, m_currentframe);
}
