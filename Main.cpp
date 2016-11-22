#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "GameEngine.h"

using namespace std;

#define FPS 60

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void checkIfImageExist(SDL_Surface*);

int main(int argc, char* argv[])
{
    // Init
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Space Invaders", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
    Mix_Chunk* backgroundMusic = Mix_LoadWAV("res/Solving1.wav");
    Mix_PlayChannel(-1, backgroundMusic, -1);
    // TODO: add sound effects!

    TTF_Font* font = TTF_OpenFont("res/djbgetdigital.ttf", 24);
    string score = "Score: ";
    SDL_Color white = { 255, 255, 255 };
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, score.c_str(), white);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    int scoreWidth = scoreSurface->w;
    int scoreHeight = scoreSurface->h;
    SDL_Rect scoreRect = { 250, 0, scoreWidth, scoreHeight };
    SDL_FreeSurface(scoreSurface);

    SDL_Surface* ship = SDL_LoadBMP("ship.bmp");
    checkIfImageExist(ship);

    int w = ship->w, h = ship->h;
    int x = 368, y = 500;
    SDL_Rect dest = { x,y,w,h };
    Uint32 black = SDL_MapRGB(ship->format, 0, 0, 0);
    SDL_SetColorKey(ship, SDL_ENABLE, black);

    SDL_Texture* shipTexture = SDL_CreateTextureFromSurface(renderer, ship);
    SDL_FreeSurface(ship);

    SDL_Surface* bg = SDL_LoadBMP("bg.bmp");
    checkIfImageExist(bg);
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);

    const int TPR = 1000 / FPS; // Time Per Rotation
    int rotations = 0;
    int dir = 1;

    bool keepGoing = true;
    bool moving = false;

    while (keepGoing) {
        Uint32 nextTick = SDL_GetTicks() + TPR;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: keepGoing = false; break;
            case SDL_MOUSEBUTTONDOWN: {
                // Mix_PlayChannel(-1, click, 0); // shooting sound!
                SDL_Point point = { event.button.x, event.button.y };
                if (SDL_PointInRect(&point, &dest) &&
                    event.button.button == SDL_BUTTON_LEFT) {
                    moving = true;
                }
            } break;
            case SDL_MOUSEMOTION:
                if (moving) {
                    x += event.motion.xrel;
                    y += event.motion.yrel;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                moving = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) { // add boundary checks
                case SDLK_ESCAPE: keepGoing = false; break;
                case SDLK_RIGHT: x += 10; break;
                case SDLK_LEFT:  x -= 10; break;
                }
                break;
            }
        }

        rotations++;
        string rotationsString = to_string(rotations);
        SDL_Surface* rotationsSurface = TTF_RenderText_Solid(font, rotationsString.c_str(), white);
        SDL_Texture* rotationsTexture = SDL_CreateTextureFromSurface(renderer, rotationsSurface);
        SDL_Rect rotationsRect = { 400, 300, rotationsSurface->w, rotationsSurface->h };

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
        dest.x = x; dest.y = y;
        SDL_RenderCopy(renderer, shipTexture, NULL, &dest);
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        SDL_RenderCopy(renderer, rotationsTexture, NULL, &rotationsRect);
        SDL_RenderPresent(renderer);

        SDL_FreeSurface(rotationsSurface);
        SDL_DestroyTexture(rotationsTexture);

        int delay = nextTick - SDL_GetTicks();
        if (delay > 0)
            SDL_Delay(delay);
    }

    // Clear heap
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(shipTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

void checkIfImageExist(SDL_Surface* image) {
    if (image == nullptr) {
        cout << "Could not locate image" << endl;
        exit(13);
    }
}