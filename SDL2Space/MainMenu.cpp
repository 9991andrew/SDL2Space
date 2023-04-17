#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderer) : renderer(renderer), Font(nullptr), selectedbutton(Button::None), hoveredbutton(Button::None), stitlesurface(nullptr), ttitlesurface(nullptr) {
    if (TTF_Init() == -1) {
        SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
        return;
    }

    Font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 12);
    if (Font == nullptr) {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        return;
    }
   
    SDL_Color color{ 255,255,255 };
    stitlesurface = TTF_RenderText_Solid(Font, "Cosmic Defenders", color);
    ttitlesurface = SDL_CreateTextureFromSurface(renderer, stitlesurface);
    titlerect = { 25,50,stitlesurface->w, stitlesurface->h };

    buttonrects[Button::Play] = {120, 100, 80, 16};
    buttonrects[Button::Options] = { 120,160,80,16 };
    buttonrects[Button::Exit] = { 120, 220, 80, 16 };
}

MainMenu::~MainMenu() {
    TTF_CloseFont(Font);
    TTF_Quit();
}

void MainMenu::handleInput(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_Point point = { x,y };
        for (const auto& buttonrect : buttonrects) {
            if (SDL_PointInRect(&point, &buttonrect.second)) {
                selectedbutton = buttonrect.first;
                break;
            }
        }
    }
    else if (event.type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_Point point = { x, y };
        bool found = false;
        for (const auto& buttonrect : buttonrects) {
            if (SDL_PointInRect(&point, &buttonrect.second)) {
                hoveredbutton = buttonrect.first;
                found = true;
                break;
            }
        }
        if (!found) {
            hoveredbutton = Button::None;
        }
    }
}
void MainMenu::update(float deltaTime) {

}
void MainMenu::draw(SDL_Renderer* renderer) {
    SDL_Color textColor = { 255, 255, 255, 255 }; // White text color
    SDL_Color selectedColor = { 0, 255, 0, 255 }; // Green selected color
    SDL_Color rectangleColor = { 200, 200, 200, 255 };
    for (const auto& buttonRect : buttonrects) {
        SDL_SetRenderDrawColor(renderer, rectangleColor.r, rectangleColor.g, rectangleColor.b, rectangleColor.a);
        SDL_RenderFillRect(renderer, &buttonRect.second);
        
        SDL_Surface* textSurface = nullptr;
        const char* buttonText = "";

        switch (buttonRect.first) {
        case Button::Play:
            buttonText = "Play";
            break;
        case Button::Options:
            buttonText = "Options";
            break;
        case Button::Exit:
            buttonText = "Exit";
            break;
        default:
            break;
        }

        if (buttonRect.first == hoveredbutton) {
            textSurface = TTF_RenderText_Solid(Font, buttonText, selectedColor);
        }
        else {
            textSurface = TTF_RenderText_Solid(Font, buttonText, textColor);
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textrect;
        textrect.x = buttonRect.second.x + (buttonRect.second.w - textSurface->w) / 2;
        textrect.y = buttonRect.second.y + (buttonRect.second.h - textSurface->h) / 2;
        textrect.w = textSurface->w;
        textrect.h = textSurface->h;
        SDL_RenderCopy(renderer, textTexture, nullptr, &textrect);
        SDL_RenderCopy(renderer, ttitlesurface, nullptr, &titlerect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

MainMenu::Button MainMenu::getSelectedButton() const {
    return selectedbutton;
}