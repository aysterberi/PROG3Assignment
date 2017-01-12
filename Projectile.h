/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Sprite.h"

namespace Engine {
    class Projectile : public Sprite {
    public:
        using Sprite::Sprite;
        ~Projectile();
        void react(SDL_Event&) override;
        void tick(GameEngine &) override;
    private:
		const int PROJECTILE_VELOCITY = 5;
    };
}
#endif