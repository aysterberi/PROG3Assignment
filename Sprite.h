#ifndef SPRITE_H
#define SPRITE_H

#include "GameObject.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
namespace Engine {
    class Sprite :
        public GameObject
    {
    public:
        virtual void draw() = 0;
        virtual ~Sprite();
        SDL_Texture* getTexture() const { return spriteTexture; }
    protected:
        Sprite(const SDL_Rect& rect, SDL_Texture* texture);
    private:
        SDL_Rect rect;
        SDL_Texture* spriteTexture;
        Sprite(const Sprite&) = delete;
        const Sprite& operator=(const Sprite&) = delete;
    };
}
#endif

