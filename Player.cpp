#include "Player.h"
#include "Sprite.h"
#include "GameEngine.h"
#include <iostream>

namespace SpaceGame {

    Player::~Player() {

    }

    void Player::react(SDL_Event& event)
    {	
		//pressing down?
		if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			//update velocity
			switch(event.key.keysym.sym)
			{
			case SDLK_a:
			case SDLK_LEFT:
				setVelocity({ -maxSpeed, });
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				setVelocity({ +maxSpeed, });
				break;
			case SDLK_LCTRL:
				shooting = true;
				break;
			}
		}
		if(event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch(event.key.keysym.sym)
			{
			case SDLK_a:
			case SDLK_LEFT:
				setVelocity({ +maxSpeed, });
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				setVelocity({ -maxSpeed, });
				break;
			case SDLK_LCTRL:
				shooting = false;
				break;
			default:
				break;
			}
		}
    }
	void Player::move(float timeStep)
    {
		std::cout << "move called with dt " << timeStep;
		Sprite::move(timeStep);
		if (getPosition().x < 0)
		{
			setPosition({ 0, });
		}
		std::cout << "position is " << getPosition().x << " , " << getPosition().y;
    }
    void Player::tick(Engine::GameEngine &engine)
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
