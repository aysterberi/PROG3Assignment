#include "Enemy.h"

namespace Engine {

    Enemy::Enemy(SDL_Texture *, SDL_Rect, bool, int dir):
        Sprite(texture, rect, drawn), direction(dir) {

    }
    Enemy::~Enemy() {
        SDL_DestroyTexture(this->getTexture());
    }

    void Enemy::react(SDL_Event)
    {
    }

    void Enemy::tick(GameEngine &engine) {
        this->incrementRectX(direction);
    }


}