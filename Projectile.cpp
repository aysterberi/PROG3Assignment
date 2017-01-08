#include "Projectile.h"

namespace Engine {

    Projectile::~Projectile() {
        SDL_DestroyTexture(this->getTexture());
    }
    void Projectile::react(SDL_Event)
    {
    }
    void Projectile::tick(GameEngine &)
    {
    }
}