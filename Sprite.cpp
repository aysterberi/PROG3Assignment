#include "Sprite.h"

namespace Engine {
    Sprite::Sprite(SDL_Texture * SpTexture,
        SDL_Rect SpDstRect,
        bool SpDrawn = true) 
        : texture(SpTexture), rect(SpDstRect), drawn(SpDrawn) {

    }

    Sprite::~Sprite() {
		SDL_DestroyTexture(texture);
    }

    void Sprite::incrementRectX(int inc) {
        rect.x += inc;
    }

    void Sprite::incrementRectY(int inc) {
        rect.y += inc;
    }
	void Sprite::react(SDL_Event event)
	{
	}
	void Sprite::tick(GameEngine & engine)
	{
	}
}