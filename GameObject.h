#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL.h>

class GameObject
{
public:
    virtual void draw() = 0;
    virtual ~GameObject();
    SDL_Rect getRect() const { return rect; }
protected:
    GameObject(const SDL_Rect& r);
private:
    SDL_Rect rect;
};

#endif

