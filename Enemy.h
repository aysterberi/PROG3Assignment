#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
namespace SpaceGame {
    class Enemy :
        public Engine::Sprite
    {
    public:
        Enemy(SDL_Texture*, SDL_Rect, bool, int);
        ~Enemy();
        void react(SDL_Event) override;
        void tick(Engine::GameEngine &engine) override;
        void invertDirection() { direction = -direction; }
    private:
        SDL_Texture* texture;
        SDL_Rect rect;
        bool drawn;
        int direction;
    };

}

#endif
