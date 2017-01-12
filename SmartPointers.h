/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H
#include <SDL.h>
#include <memory>
#include "Graphic.h"

namespace Engine
{

	typedef std::shared_ptr<SDL_Texture> TextureShPtr;
	typedef std::shared_ptr<Graphic> GraphicShPtr;
}
#endif