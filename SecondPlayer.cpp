#include "SecondPlayer.h"
namespace SpaceGame
{
	void SecondPlayer::react(SDL_Event & event)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_j:
			addPositionX(-5);
			break;
		case SDLK_l:
			addPositionX(+5);
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