#include "Projectile.h"

namespace Engine {
    Projectile::~Projectile() {
        SDL_DestroyTexture(this->getTexture());
    }
    void Projectile::react(SDL_Event & event)
    {
    }
    void Projectile::tick(GameEngine &engine)
    {
		incrementRectY(-PROJECTILE_VELOCITY); //move up
		//if (getRect().y < 0)
		//{
		//	setDrawn(false);
		//}
    }
}