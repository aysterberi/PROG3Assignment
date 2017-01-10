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