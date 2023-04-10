#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
public:
    GameObject(int x, int y);

    virtual void update(float deltaTime) = 0; // Pure virtual function, making this class abstract

    int getX() const { return x; }
    int getY() const { return y; }

protected:
    int x, y;
};

#endif // GAMEOBJECT_H
