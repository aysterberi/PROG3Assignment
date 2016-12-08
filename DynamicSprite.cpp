#include "DynamicSprite.h"
#include "Sprite.h"
#include "GameObject.h"
#include "GameEngine.h"
namespace Engine {

    DynamicSprite::DynamicSprite(const SDL_Rect & rect,
        SDL_Texture * texture, int numberOfImages): Sprite(rect, texture),
        numberOfImages(numberOfImages) {
    }

    int DynamicSprite::getNumberOfImages() const
    {
        return numberOfImages;
    }

    void DynamicSprite::draw() {
        SDL_RenderCopy(gameEngine.getRenderer(), getTexture(), NULL, &getRect());
    }

    DynamicSprite::~DynamicSprite()
    {
    }
}