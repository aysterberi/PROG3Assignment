#ifndef STATICSPRITE_H
#define STATICSPRITE_H
#include "Sprite.h"
namespace Engine {
    class StaticSprite :
        public Sprite
    {
    public:
        StaticSprite(SDL_Rect& rect, SDL_Texture* texture);
        ~StaticSprite();
        void draw();
    protected:
    private:
    };
}
#endif