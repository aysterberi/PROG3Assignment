#include "Sprite.h"

namespace Engine {
    Sprite::Sprite(SDL_Texture * SpTexture,
        SDL_Rect SpDstRect,
        bool SpDrawn = true) 
        : texture(SpTexture), rect(SpDstRect), drawn(SpDrawn) {

    }

    Sprite::~Sprite() {
        texture = NULL;
    }

    void Sprite::incrementRectX(int inc) {
        rect.x += inc;
    }

    void Sprite::incrementRectY(int inc) {
        rect.y += inc;
    }
}