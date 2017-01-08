#include "Player.h"
#include "Sprite.h"

Player::Player(Sprite * sprite): Sprite(sprite->getTexture(), sprite->getRect(), sprite->isDrawn())
{
}

Player::~Player()
{
}

void Player::react(SDL_Event event)
{
	switch(event.key.keysym.sym)
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
		shoot();
		break; 
	default:
		break;
	}
}
void Player::tick()
{
}
void Player::moveLeft()
{
	incrementRectX(-5);
}

void Player::moveRight()
{
	incrementRectX(+5);
}


void Player::shoot()
{
	
}


