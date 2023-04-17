#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL.h>
class GameObject {
public:
    GameObject(int x, int y);
    
    virtual void update(float deltaTime) = 0; // Pure virtual function, making this class abstract
    virtual void draw(SDL_Renderer* renderer) = 0;
    int getX() const { return x; }
    int getY() const { return y; }
    SDL_Rect& GetDstRect() { return m_dstRect; }
    void setMarkedForDel(bool m) { this->markedfordel = m; }
    bool isMarkedForDel() { return markedfordel; }
protected:
    int x, y;
    SDL_Rect m_dstRect;
    bool m_isactive;

    bool markedfordel;
};

#endif // GAMEOBJECT_H
