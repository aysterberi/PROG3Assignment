#include "DynamicSprite.h"
#include "Sprite.h"
#include "GameObject.h"
namespace Engine {

    DynamicSprite::DynamicSprite(const SDL_Rect & rect,
        SDL_Texture * texture, int numberOfImages): Sprite(rect, texture),
        numberOfImages(numberOfImages) {
    }

    int DynamicSprite::getNumberOfImages() const
    {
        return numberOfImages;
    }

    void DynamicSprite::draw()
    {
    }

    DynamicSprite::~DynamicSprite()
    {
    }
}