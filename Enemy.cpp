#include "Enemy.h"
#include "GameEngine.h"

namespace SpaceGame {

    Enemy::Enemy(SDL_Texture * texture, SDL_Rect rect, bool drawn = true, int dir = 3) :
        Sprite(texture, rect, drawn), direction(dir) {
    }
    Enemy::~Enemy() {
        SDL_DestroyTexture(this->getTexture());
    }

    void Enemy::react(SDL_Event & event) {}

    void Enemy::tick(Engine::GameEngine &engine) {
		if(engine.hasProjectileCollision(*this))
		{
			setDrawn(false);
		}
        this->incrementRectX(direction);
        if (this->getRect().x > engine.getScreenWidth()) {
            this->incrementRectY(150);
            invertDirection();
        }
        else if (this->getRect().x < 0) {
            this->incrementRectY(150);
            invertDirection();
        }
    }
}