#include "ResourceLoader.h"
#include <SDL_image.h>
#include "GameEngine.h"
#include <iostream>

namespace Engine
{
	extern GameEngine engine;

	ResourceLoader::ResourceLoader()
	{
	}


	ResourceLoader::~ResourceLoader()
	{
	}

	void ResourceLoader::loadTexture(std::string key, std::string path)
	{
		if (key.empty() | path.empty())
		{
			std::uncaught_exception();
			std::cout << "Either key or path given was empty.";
			return;
		}
		//create a surface
		SDL_Surface* surface = IMG_Load(path.c_str());
		SDL_Texture* texture = engine.newTexture(surface);
		textureMap.emplace(key, texture);
	}

	void ResourceLoader::loadFont(std::string key, std::string path, int ptsize)
	{
	}

	void ResourceLoader::loadAudio(std::string key, std::string path)
	{
	}

	bool ResourceLoader::unload(std::string key)
	{
		return false;
	}

	SDL_Texture * ResourceLoader::fetchTexture(std::string key)
	{
		return &textureMap.at(key);
	}

	TTF_Font * ResourceLoader::fetchFont(std::string key)
	{
		return nullptr;
	}

	Mix_Music * ResourceLoader::fetchAudio(std::string key)
	{
		return nullptr;
	}

}
