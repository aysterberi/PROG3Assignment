#include "StaticSprite.h"
#include "Sprite.h"
#include "GameObject.h"

namespace Engine {

    StaticSprite::StaticSprite(SDL_Rect & rect, SDL_Texture * texture):
        Sprite(rect, texture) {
    }

    StaticSprite::~StaticSprite() {
    }
    void StaticSprite::draw()
    {
    }
}