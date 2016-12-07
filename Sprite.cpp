#include "Sprite.h"
namespace Engine {

    Sprite::Sprite(const SDL_Rect& rect, SDL_Texture* texture) :
        GameObject(rect), spriteTexture(texture) {
    }

    Sprite::~Sprite()
    {
    }
}