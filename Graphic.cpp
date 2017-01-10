#include "Graphic.h"
#include "GameEngine.h"
#include <iostream>


Engine::Graphic::Graphic(SDL_Texture * texture, SDL_Renderer * renderer, int width, int height) :
	_texture(texture),
	_renderer(renderer),
	_width(width),
	_height(height)
{
}

void Engine::Graphic::render(int x, int y)
{
	SDL_Rect rect = { x,y, _width, _height };
	SDL_RenderCopy(_renderer, _texture, NULL, &rect);
}

Engine::Graphic::~Graphic()
{
	SDL_DestroyTexture(_texture);
	_renderer = nullptr;
}

