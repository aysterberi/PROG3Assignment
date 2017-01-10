#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <SDL_hints.h>
#include <unordered_map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <map>

namespace Engine
{

	class ResourceLoader
	{
	public:
		ResourceLoader();
		~ResourceLoader();
		//loads a texture from a file path
		void loadTexture(std::string key, std::string path);
		void loadFont(std::string key, std::string path, int ptsize);
		void loadAudio(std::string key, std::string path);

		//unloads a resource given a key, true if successful
		bool unload(std::string key);

		SDL_Texture* fetchTexture(std::string key);
		TTF_Font* fetchFont(std::string key);
		Mix_Music* fetchAudio(std::string key);

	private:
		static std::map<std::string, SDL_Texture> textureMap;
		static std::map<std::string, TTF_Font> fontMap;
		static std::map<std::string, Mix_Music> audioMap;
	};
}

#endif
