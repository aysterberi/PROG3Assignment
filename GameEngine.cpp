#include "GameEngine.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <memory>
#include "STimer.h"

#define DEFAULT_FPS 60;
namespace Engine {

	//constructors
	GameSettings engineSettings;
	GameEngine::GameEngine() {
		window = nullptr;
		backgroundSurface = nullptr;
		backgroundTexture = nullptr;
		renderer = nullptr;
		backgroundMusic = nullptr;
		player = nullptr;
		FPS = DEFAULT_FPS;
	}
	GameEngine::GameEngine(GameSettings game_settings)
	{
		window = nullptr;
		backgroundSurface = nullptr;
		backgroundTexture = nullptr;
		renderer = nullptr;
		backgroundMusic = nullptr;
		player = nullptr;
		engineSettings = game_settings;
		FPS = game_settings.fps;
	}
	bool GameEngine::createWindow()
	{
		window = SDL_CreateWindow(engineSettings.title, 100, 100, engineSettings.width, engineSettings.height, 0);
		if (window == nullptr) {
			printf("Unable to create window: %s\n", SDL_GetError());
			return false;
		}
		return true;
	}

	//configuration
	void GameEngine::setBackground(std::string path) {
		SDL_Surface* adjustedSurface = nullptr;
		SDL_Surface* initialSurface = IMG_Load(path.c_str());

		if (initialSurface == nullptr) {
			printf("Unable to load image %s: %s\n", path.c_str(), IMG_GetError());
		}

		adjustedSurface = SDL_ConvertSurface(initialSurface, backgroundSurface->format, 0);
		if (adjustedSurface == nullptr) {
			printf("Unable to adjust image %s: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(initialSurface);
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, adjustedSurface);
		SDL_FreeSurface(adjustedSurface);
	}
	void GameEngine::setBackgroundMusic(std::string path) {
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096))
			printf("Error loading audio: %s\n", Mix_GetError());

		backgroundMusic = Mix_LoadMUS(path.c_str());

		if (!backgroundMusic)
			printf("Error playing audio: %s\n", Mix_GetError());

		Mix_PlayMusic(backgroundMusic, -1);
		musicPlaying = true;
	}

	//loop initialisation and execution
	bool GameEngine::init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			printf("Unable  to initialize SDL: %s\n", SDL_GetError());
			return false;
		}

		if (!createWindow())
			return false;

		if (IMG_Init(IMG_INIT_PNG) == 0) {
			printf("Unable to initialize SDL_image: %s\n", IMG_GetError());
			return false;
		}

		if (TTF_Init() == -1) {
			printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
			return false;
		}

		if (Mix_Init(MIX_INIT_OGG) == 0) {
			printf("Unable to initialize SDL_mixer: %s\n", Mix_GetError());
			return false;
		}

		if (backgroundSurface == nullptr)
			backgroundSurface = SDL_GetWindowSurface(window);

		if (renderer == nullptr)
			renderer = createRenderer(window);
		SDL_GL_SetSwapInterval(0);
		return true;
	}
	void GameEngine::gameLoop() {
		bool quit = false;

		while (!quit) {
			Uint32 nextTick = SDL_GetTicks() + FPS;
			SDL_Event event;
			size_t numberOfProjectiles = projectiles.size();

			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT: quit = true; break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: quit = true; break;
					case SDLK_y:
						if (!gameStarted) {
							//startNewGame();
							gameStarted = true;
						}
						break;
					case SDLK_F8: toggleMusic(); break;
					default:
						if (player != nullptr)
							player->react(event);
						for (auto sprite : gameSprites)
						{
							if (sprite != nullptr)
								sprite->react(event);
						}
						for (auto sprite : sprites)
						{
							sprite->react(event);
						}
						break;
					}
				}
			}

			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);
			moveMovables();
			//moveAll(100.0);
			renderEverything();
		}
	}

	//Loop logic
	void GameEngine::moveMovables() {
		if (gameStarted) {
			//for (auto var : projectiles)
			//{
			//	var->tick(*this);
			//}
			for (Sprite* var : sprites)
			{
				if (var != nullptr)
					var->tick(*this);
			}
			//player->tick(*this);
			//moveOrDestroyProjectile(projectiles);
		}
	}
	void GameEngine::moveOrDestroyProjectile(std::vector<Sprite*>) {
		if (!projectiles.empty())
		{


			for (auto i = 0; i < projectiles.size(); i++) {
				auto projectile = projectiles.at(i);
				if (projectile->getPosition().y < 0) {
					delete projectile;
					projectiles.erase(projectiles.begin() + i);
					break;
				}
				for (auto var : gameSprites) {

					if (SDL_HasIntersection(&projectile->getRect(), &var->getRect()) && var->isDrawn()) {
						delete projectile;
						projectiles.erase(projectiles.begin() + i);
						var->setDrawn(false);
						break;
					}
				}
			}
		}
	}
	void GameEngine::renderEverything() {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
		//for (std::pair<std::string, Sprite*> var : gameObjects) {
		//	if (var.second->isDrawn())
		//		SDL_RenderCopy(renderer, var.second->getTexture(), NULL, &var.second->getRect());
		//}
		//for (auto var : gameSprites) {
		//	if (var->isDrawn())
		//		SDL_RenderCopy(renderer, var->getTexture(), NULL, &var->getRect());
		//}
		for (Sprite* var : projectiles) {
			SDL_RenderCopy(renderer, var->getTexture(), NULL, &var->getRect());
		}
		for (auto sprite : sprites)
		{
			sprite->render();
		}
		SDL_RenderPresent(renderer);
	}

	//collision handling
	bool GameEngine::hasCollision(Sprite & sprite)
	{
		bool crash = false;
		for (auto item : sprites)
		{
			SDL_Rect* a(&sprite.getRect());
			SDL_Rect* b(&item->getRect());
			if (item != &sprite)
			{
				if (SDL_HasIntersection(a, b))
				{
					crash = true;
				}
			}
		}
		return crash;
	}

	bool GameEngine::hasProjectileCollision(Sprite & sprite)
	{
		for (auto projectile : projectiles)
		{
			if (!projectile->isDrawn())
			{
				return false;
			}
			if (SDL_HasIntersection(&sprite.getRect(), &projectile->getRect()))
				return true;
		}
		return false;
	}

	//Graphic utilities
	GraphicShPtr GameEngine::createGraphic(std::string path)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		//create raw graphic pointer
		SDL_Texture* texture = newTexture(surface);
		//create new Graphic object and create a shared_ptr
		GraphicShPtr ptr(new Graphic(texture, getRenderer(), surface->w, surface->h));

		//free surface
		SDL_FreeSurface(surface);
		//return this to the Sprite
		return ptr;
	}
	GraphicShPtr GameEngine::createTextGraphic(TTF_Font* font, std::string text, SDL_Color color)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		//create raw graphic pointer
		SDL_Texture* texture = newTexture(surface);
		//create new Graphic object and create a shared_ptr
		GraphicShPtr ptr(new Graphic(texture, getRenderer(), surface->w, surface->h));
		//free surface
		SDL_FreeSurface(surface);
		//return this to the Sprite
		return ptr;
	}

	//Sprite handling
	void GameEngine::addSprite(Sprite* sprite)
	{
		sprites.emplace_back(sprite);
	}
	void GameEngine::addProjectile(Sprite* projectile)
	{
		projectiles.emplace_back(projectile);
	}
	void GameEngine::removeGameObject(std::string key)
	{
		gameObjects.erase(key);
	}

	//Music handling
	void GameEngine::toggleMusic() {
		if (musicPlaying)
		{
			volume = Mix_VolumeMusic(-1);
			Mix_VolumeMusic(0); //set volume to 0 for all channels (-1)
			musicPlaying = false;
		}
		else {
			Mix_VolumeMusic(volume); //restore original volume
			musicPlaying = true;
		}
	}

	//internal utilities
	SDL_Texture * GameEngine::newTexture(SDL_Surface* surface)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		return texture;
	}
	SDL_Renderer* GameEngine::createRenderer(SDL_Window* window) {
		return SDL_CreateRenderer(window, -1, 0);
	}

	//destructor
	GameEngine::~GameEngine() {
		for (std::pair<std::string, Sprite*> var : gameObjects) {
			delete var.second;
		}
		gameObjects.clear();
		projectiles.clear();
		Mix_FreeMusic(backgroundMusic);
		Mix_CloseAudio();
		SDL_FreeSurface(backgroundSurface);
		SDL_DestroyTexture(backgroundTexture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}

}