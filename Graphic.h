/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <SDL.h>

namespace Engine {
	class Graphic
	{
	public:
		Graphic(SDL_Texture*, SDL_Renderer*, int w, int h);
		int width() { return _width; }
		int height() { return _height; }
		void render(int x, int y);
		SDL_Texture* texture() { return _texture; };
		~Graphic();
	private:
		SDL_Texture* _texture;
		SDL_Renderer* _renderer;
		int _width;
		int _height;
	};
}
#endif