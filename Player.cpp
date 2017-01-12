/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

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
		//if we're dead
		//we can't react
		if (!alive)
			return;

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
			if (alive)
			{
				Engine::Position textPosition{ 150,250 };
				SDL_Color textColor{ 255, 255, 255 };
				Engine::Text* text = new Engine::Text(
					"res/djbgetdigital.ttf",
					48, //font size
					textPosition,
					textColor, //white
					"You lose!",
					engine);
				engine.addMessage(text, -1);
				engine.stop();
				alive = false;
			}

		}

	}

}
