#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
namespace Engine {
    class Enemy :
        public Sprite
    {
    public:
        Enemy(SDL_Texture*, SDL_Rect, bool, int);
        ~Enemy();
        void react(SDL_Event) override;
        void tick(GameEngine &) override;
        void setDirection() { direction = -direction; }
    private:
        SDL_Texture* texture;
        SDL_Rect rect;
        bool drawn;
        int direction;
    };

}

#endif
