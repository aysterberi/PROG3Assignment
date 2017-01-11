#include "Projectile.h"
#include <iostream>

namespace Engine {
    Projectile::~Projectile() {
		Sprite::~Sprite();
    }
    void Projectile::react(SDL_Event & event)
    {
    }
    void Projectile::tick(GameEngine &engine)
    {
		//std::cout << "Projectile moving one step up.";
		addPositionY(-PROJECTILE_VELOCITY); //move up
		if(getPosition().y < 0)
		{
			setDrawn(false);
		}
    }
}
