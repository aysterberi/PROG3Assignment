/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"
#include <iostream>

namespace SpaceGame {
    class Player : public Engine::Sprite
    {
    public:
        using Sprite::Sprite;
        ~Player();
        void react(SDL_Event& event) override;
	    void tick(Engine::GameEngine &) override;
    protected:
		bool shooting;
		bool alive = true;
    private:
		float maxSpeed = 20.0;
    };
}
#endif
