/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

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
        if (this->getPosition().x > engine.getScreenWidth() - 40) {
            this->addPositionY(50);
            invertDirection();
        }
        else if (this->getPosition().x < 0) {
            this->addPositionY(50);
            invertDirection();
        }
    }
}