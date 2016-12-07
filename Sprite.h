#ifndef SPRITE_H
#define SPRITE_H

#include "GameObject.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Sprite :
    public GameObject
{
public:
    Sprite(const SDL_Rect& r, SDL_Texture* texture);
    ~Sprite();
protected:
    SDL_Texture* getTexture() const { return spriteTexture; }
private:
    SDL_Texture* spriteTexture;
};

#endif

