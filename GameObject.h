#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
namespace Engine {
    class GameObject
    {
    public:
		struct Position
		{
			int xPos;
			int yPos;
		};
		void setPosition(int xPos, int yPos);
		Position getPosition();
        virtual void draw() = 0;
        virtual ~GameObject();
        SDL_Rect getRect() const { return rect; }
    protected:
        GameObject(const SDL_Rect& rect);
    private:
		Position objectPosition;
        SDL_Rect rect;
        GameObject(const GameObject&) = delete;
        const GameObject& operator=(const GameObject&) = delete;
    };
}
#endif

