/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include <iostream>

namespace SpaceGame {
    class Enemy :
        public Engine::Sprite
    {
    public:
		using Sprite::Sprite;
        ~Enemy();
        void react(SDL_Event&) override;
        void tick(Engine::GameEngine &engine) override;
        void invertDirection() { direction = -direction; }
    private:
        SDL_Texture* texture;
        SDL_Rect rect;
        bool drawn;
		int direction = 3;
    };

}

#endif
