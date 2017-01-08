#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Sprite.h"
class Projectile : public Engine::Sprite
{
public:
	using Sprite::Sprite;
	~Projectile();
};

#endif