#include "Player.h"
#include "Sprite.h"
#include "GameEngine.h"
#include <iostream>
#include "Text.h"

namespace SpaceGame {

	Player::~Player() {

	}

	void Player::react(SDL_Event& event)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
		case SDLK_LEFT:
			addPositionX(-5);
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			addPositionX(+5);
			break;
		case SDLK_LCTRL:
			shooting = true;
			break;
		default:
			break;
		}
		////pressing down?
		//if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
		//{
		//	//update velocity
		//	switch(event.key.keysym.sym)
		//	{
		//	case SDLK_a:
		//	case SDLK_LEFT:
		//		setVelocity({ -maxSpeed, });
		//		break;
		//	case SDLK_d:
		//	case SDLK_RIGHT:
		//		setVelocity({ +maxSpeed, });
		//		break;
		//	case SDLK_LCTRL:
		//		shooting = true;
		//		break;
		//	}
		//}
		//if(event.type == SDL_KEYUP && event.key.repeat == 0)
		//{
		//	switch(event.key.keysym.sym)
		//	{
		//	case SDLK_a:
		//	case SDLK_LEFT:
		//		setVelocity({ +maxSpeed, });
		//		break;
		//	case SDLK_d:
		//	case SDLK_RIGHT:
		//		setVelocity({ -maxSpeed, });
		//		break;
		//	case SDLK_LCTRL:
		//		shooting = false;
		//		break;
		//	default:
		//		break;
		//	}
		//}
	}
	void Player::move(float timeStep)
	{
		//std::cout << "move called with dt " << timeStep;
		//Sprite::move(timeStep);
		//if (getPosition().x < 0)
		//{
		//	setPosition({ 0, });
		//}
		//std::cout << "position is " << getPosition().x << " , " << getPosition().y;
	}
	void Player::tick(Engine::GameEngine &engine)
	{
		if (shooting)
		{
			std::cout << "shooting!";
			Engine::Projectile* shot = new Engine::Projectile(
				"res/projectile.png",
				{ getPosition().x + 30,	getPosition().y + 10 },
				engine);
			engine.addProjectile(shot);
			shooting = false;
		}
		if (engine.hasCollision(*this))
		{
			//TODO: do something
			std::cout << "Oops, I collided.";
			Engine::Position textPosition{ 150,250 };
			SDL_Color textColor{ 255, 255, 255 };
			Engine::Text* text = new Engine::Text(
				"res/djbgetdigital.ttf",
				48, //font size
				textPosition,
				textColor, //white
				"Ha! You lose.",
				engine);
			engine.addSprite(text);
		}

	}

}
