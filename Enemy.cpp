#include "Enemy.h"
#include "GameEngine.h"

namespace SpaceGame {

    Enemy::~Enemy() {
        SDL_DestroyTexture(this->getTexture());
    }

    void Enemy::react(SDL_Event & event) {}

    void Enemy::tick(Engine::GameEngine &engine) {
		if(engine.hasProjectileCollision(*this))
		{
			setDrawn(false);
		}
        this->addPositionX(direction);
        if (this->getPosition().x > engine.getScreenWidth()) {
            this->addPositionY(150);
            invertDirection();
        }
        else if (this->getPosition().x < 0) {
            this->addPositionY(150);
            invertDirection();
        }
    }
}