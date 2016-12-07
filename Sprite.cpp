#include "Sprite.h"

Sprite::Sprite(const SDL_Rect& r, SDL_Texture* texture): 
    GameObject(r), spriteTexture(texture) {
}

Sprite::~Sprite()
{
}
