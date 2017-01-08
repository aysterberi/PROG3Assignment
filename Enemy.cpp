#include "Enemy.h"

namespace Engine {

    Enemy::~Enemy() {
        SDL_DestroyTexture(this->getTexture());
    }
}