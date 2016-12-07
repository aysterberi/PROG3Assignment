#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
namespace Engine {
    class GameObject
    {
    public:
        virtual void draw() = 0;
        virtual ~GameObject();
        SDL_Rect getRect() const { return rect; }
    protected:
        GameObject(const SDL_Rect& rect);
    private:
        SDL_Rect rect;
        GameObject(const GameObject&) = delete;
        const GameObject& operator=(const GameObject&) = delete;
    };
}
#endif

