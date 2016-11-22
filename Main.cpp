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

int main(int argc, char* argv[]) {
    GameEngine gameEngine;
    if (!gameEngine.init())
        cout << "Failed to initialize game engine" << endl;

    return 0;
}

