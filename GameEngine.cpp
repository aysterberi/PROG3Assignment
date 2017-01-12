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
	void GameEngine::loop() {
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
			//update all projectiles
			for (auto var : projectiles)
			{
				if (var != nullptr)
				{
					var->tick(*this);
				}

			}
			//execute sprite logic
			for (Sprite* var : sprites)
			{
				if (var != nullptr)
					var->tick(*this);
			}
			//clean up isDrawn() false
			destroyProjectiles();
		}
	}
	void GameEngine::stop()
	{
		gameStarted = false;
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
			if (var != nullptr)
			{
				SDL_RenderCopy(renderer, var->getTexture(), NULL, &var->getRect());
			}
		}
		for (auto sprite : sprites)
		{
			sprite->render();
		}
		for (auto message : messages)
		{
			message->render();
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
			if(!projectiles.empty())
			{
				for (int i = projectiles.size() - 1; i >= 0; i--)
				{
					if(projectiles.at(i)->isDrawn() && 
						(SDL_HasIntersection(&sprite.getRect(), &projectiles.at(i)->getRect()))
						)	
					{
						Sprite* proj(projectiles[i]);
						projectiles.erase(projectiles.begin() + i);
						delete proj;
						return true;
					}

				}
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
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		//create raw graphic pointer
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);

		int textWidth = textSurface->w, textHeight = textSurface->h;

		//free surface
		SDL_FreeSurface(textSurface);

		//create new Graphic object and create a shared_ptr
		GraphicShPtr ptr(new Graphic(texture, getRenderer(), textWidth, textHeight));

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
	void GameEngine::addMessage(Sprite * sprite, int duration)
	{
		//permanent display, e.g. game over
		if (duration < 0)
		{
			messages.emplace_back(sprite);
		}

		//todo: fading messages
	}
	void GameEngine::removeGameObject(std::string key)
	{
		gameObjects.erase(key);
	}
	void GameEngine::destroyProjectiles()
	{
		if (!projectiles.empty())
		{
			for (int i = projectiles.size() - 1; i >= 0; i--)
			{
				if (!projectiles.at(i)->isDrawn())
				{
					Sprite* proj(projectiles[i]);
					projectiles.erase(projectiles.begin() + i);
					delete proj;
				}
			}
		}
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
