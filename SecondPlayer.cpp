/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#include "SecondPlayer.h"
namespace SpaceGame
{
	void SecondPlayer::react(SDL_Event & event)
	{
		//if we're dead
		//we can't react
		if (!alive)
			return;

		switch (event.key.keysym.sym)
		{
		case SDLK_j:
			addPositionX(-5);
			break;
		case SDLK_l:
			addPositionX(+5);
			break;
		case SDLK_i:
			addPositionY(-5);
			break;
		case SDLK_RCTRL:
			shooting = true;
			break;
		default:
			break;
		}
	}
	SecondPlayer::~SecondPlayer()
	{
	}

}