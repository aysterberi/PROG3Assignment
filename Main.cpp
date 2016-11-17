#include <SDL.h>
#include <iostream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void checkIfImageExist(SDL_Surface*);

int main(int argc, char* args[])
{
    // Init
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Space Invaders", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface* ship = SDL_LoadBMP("ship.bmp");
    checkIfImageExist(ship);

    int w = ship->w, h = ship->h;
    int x = 368, y = 500;
    Uint32 black = SDL_MapRGB(ship->format, 0, 0, 0);
    SDL_SetColorKey(ship, SDL_ENABLE, black);

    SDL_Texture* shipTexture = SDL_CreateTextureFromSurface(renderer, ship);
    SDL_FreeSurface(ship);

    SDL_Surface* bg = SDL_LoadBMP("bg.bmp");
    checkIfImageExist(bg);
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_FreeSurface(bg);

    bool keepGoing = true;
    while (keepGoing) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: keepGoing = false; break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) { // add boundary checks
                case SDLK_ESCAPE: keepGoing = false; break;
                case SDLK_RIGHT: x += 10; break;
                case SDLK_LEFT:  x -= 10; break;
                } break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
        SDL_Rect dest = { x, y, w, h };
        SDL_RenderCopy(renderer, shipTexture, NULL, &dest);
        SDL_RenderPresent(renderer);
    }

    // Clear heap
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(shipTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void checkIfImageExist(SDL_Surface* image) {
    if (image == nullptr) {
        cout << "Could not locate image" << endl;
        exit(13);
    }
}