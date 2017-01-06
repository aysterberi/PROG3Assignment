#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
namespace Engine {
    class Sprite {
    public:
        Sprite(SDL_Texture*, SDL_Rect, bool);
        ~Sprite();
        SDL_Texture* getTexture() const { return texture; }
        SDL_Rect getRect() const { return rect; }
        void setRectY(int newY) { rect.y = newY; }
        void setRectX(int newX) { rect.x = newX; }
        void incrementRectX(int inc);
        void incrementRectY(int inc);
        bool isDrawn() const { return drawn; }
		void setDrawn(bool newValue) { drawn = newValue; }
		void react(SDL_Event event);
    private:
        SDL_Rect rect;
        SDL_Texture* texture;
        bool drawn;
    };
}
#endif

