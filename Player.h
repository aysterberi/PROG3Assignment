#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"

class Player : public Engine::Sprite
{
public:
	using Sprite::Sprite;
	Player(Sprite*);
	~Player();
	void react(SDL_Event event);
	void tick();
private:
	void moveLeft();
	void moveRight();
	void shoot();
};

#endif
