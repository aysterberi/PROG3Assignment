/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#ifndef INVADERS_H
#define INVADERS_H
#include "GameEngine.h"

namespace SpaceGame
{
	class Invaders
	{
	public:
		Invaders();
		void createEnemies(int amount, Engine::GameEngine& context);
		~Invaders();
	};
}

#endif
