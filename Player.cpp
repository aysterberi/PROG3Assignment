#include "Player.h"
#include "Sprite.h"
#include "GameEngine.h"
#include <iostream>

namespace Engine {

    Player::~Player() {

    }

    void Player::react(SDL_Event event)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
        case SDLK_LEFT:
            moveLeft();
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            moveRight();
            break;
        case SDLK_LCTRL:
			shooting = true;
            break;
        default:
            break;
        }
    }
    void Player::tick(GameEngine &engine)
    {
		if(shooting)
		{
			engine.createProjectile("res/projectile.png", *this);
			shooting = false;
		}
		if(engine.hasCollision(*this))
		{
			//TODO: do something
			std::cout << "Oops, I collided.";
			engine.createTextTexture("res/djbgetdigital.ttf", "Ha! You lose.", 48, 255, 255, 255);
		}

    }

    void Player::moveLeft()
    {
        incrementRectX(-5);
    }

    void Player::moveRight()
    {
        incrementRectX(+5);
    }

}
