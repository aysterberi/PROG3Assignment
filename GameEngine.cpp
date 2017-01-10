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
	void GameEngine::configure (GameSettings settings)
	{
		engineSettings = settings;
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

	bool GameEngine::hasCollision(Sprite & sprite)
	{
		for (auto& other : sprites) {
			if (!other->isDrawn())
			{
			 return false;
			}
			//if (&sprite == other)
			//{
			//	//we can't collide with ourselves
			//	return false;
			//}
			if (SDL_HasIntersection(&sprite.getRect(), &other->getRect()))
				return true;
		}
		return false;
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

	void GameEngine::moveMovables() {
		if (gameStarted) {
			for (auto var : gameSprites) {
				var->tick(*this);
			}
			for (auto var : projectiles)
			{
				var->tick(*this);
			}
			for (auto var : sprites)
			{
				var->tick(*this);
			}
			//player->tick(*this);
			moveOrDestroyProjectile(projectiles);
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
	TextureShPtr GameEngine::createTexture(std::string path)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		TextureShPtr ptr(newTexture(surface), SDL_DestroyTexture);
		//free surface
		SDL_FreeSurface(surface);
		return ptr;
	}
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

	void GameEngine::addSprite(Sprite* sprite)
	{
		sprites.emplace_back(sprite);
	}
	void GameEngine::removeGameObject(std::string key)
	{
		gameObjects.erase(key);
	}

	SDL_Texture * Engine::GameEngine::newTexture(SDL_Surface* surface)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		return texture;
	}

	void GameEngine::createProjectile(std::string path, SpaceGame::Player & player)
	{
		auto x = player.getPosition().x + 30, y = player.getPosition().y + 10;
		SDL_Surface* surface = IMG_Load(path.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		int textWidth = surface->w, textHeight = surface->h;
		SDL_Rect textRect = { x, y, textWidth, textHeight };
		SDL_FreeSurface(surface);
		Projectile* projectile = new Projectile(texture, textRect, true);
		projectiles.emplace_back(projectile);
	}

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

	void GameEngine::playBackgroundMusic(std::string path) {
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096))
			printf("Error loading audio: %s\n", Mix_GetError());

		backgroundMusic = Mix_LoadMUS(path.c_str());

		if (!backgroundMusic)
			printf("Error playing audio: %s\n", Mix_GetError());

		Mix_PlayMusic(backgroundMusic, -1);
		musicPlaying = true;
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

	void GameEngine::addProjectile(Sprite* projectile)
	{
		projectiles.emplace_back(projectile);
	}
	void GameEngine::createTextTexture(std::string path, std::string message,
		int fontSize, Uint8 rColor, Uint8 gColor, Uint8 bColor) {

		TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
		SDL_Color color = { rColor, gColor, bColor };
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		int textWidth = textSurface->w, textHeight = textSurface->h;
		SDL_Rect textRectangle = { 100, 250, textWidth, textHeight };

		SDL_FreeSurface(textSurface);
		Sprite* txt = new Sprite(textTexture, textRectangle, true);
		gameObjects.insert({ message, txt });
	}

	SDL_Texture* GameEngine::loadBackgroundTexture(std::string path) {
		SDL_Surface* adjustedSurface = nullptr;
		SDL_Surface* initialSurface = IMG_Load(path.c_str());

		if (initialSurface == nullptr) {
			printf("Unable to load image %s: %s\n", path.c_str(), IMG_GetError());
			return nullptr;
		}

		adjustedSurface = SDL_ConvertSurface(initialSurface, backgroundSurface->format, 0);
		if (adjustedSurface == nullptr) {
			printf("Unable to adjust image %s: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(initialSurface);
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, adjustedSurface);
		SDL_FreeSurface(adjustedSurface);
		return backgroundTexture;
	}

	void GameEngine::setBackground(std::string path) {
		backgroundTexture = loadBackgroundTexture(path);
	}

	void GameEngine::setPlayerPath(std::string path) {
		playerPath = path;
	}

	SDL_Renderer* GameEngine::createRenderer(SDL_Window* window) {
		return SDL_CreateRenderer(window, -1, 0);
	}

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