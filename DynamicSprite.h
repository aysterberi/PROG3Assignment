#ifndef DYNAMICSPRITE_H
#define DYNAMICSPRITE_H
#include "Sprite.h"
namespace Engine {

    class DynamicSprite :
        public Sprite
    {
    public:
        DynamicSprite(const SDL_Rect& rect, SDL_Texture* texture, int numberOfImages);
        int getNumberOfImages() const;
        SDL_Texture* getTexture() const { return Sprite::getTexture(); }
        void draw();
        ~DynamicSprite();
    protected:
    private:
        int numberOfImages;
    };
}
#endif