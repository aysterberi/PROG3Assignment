/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#include "Projectile.h"
#include <iostream>

namespace Engine {
    Projectile::~Projectile() {
		Sprite::~Sprite();
    }

    void Projectile::react(SDL_Event & event) {}

    void Projectile::tick(GameEngine &engine) {
		addPositionY(-PROJECTILE_VELOCITY); //move up
		if(getPosition().y < 0) {
			setDrawn(false);
		}
    }
}
