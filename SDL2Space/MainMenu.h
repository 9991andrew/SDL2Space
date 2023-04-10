#include <map>
#ifndef MAINMENU_H
#define MAINMENU_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
class MainMenu {
public:
    enum class Button {
        None, Play, Options, Exit
    };
    MainMenu(SDL_Renderer* renderer);
    ~MainMenu();

    void handleInput(SDL_Event event);
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer);

    Button getSelectedButton() const;

private:
    SDL_Renderer* renderer;
    
    SDL_Surface* stitlesurface;
    SDL_Texture* ttitlesurface;
    SDL_Rect titlerect;
    
    TTF_Font* Font;

    std::map<Button, SDL_Rect> buttonrects;
    Button selectedbutton;
    Button hoveredbutton;
};
#endif