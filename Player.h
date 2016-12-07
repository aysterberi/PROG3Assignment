#ifndef PLAYER_H
#define PLAYER_H
#include "DynamicSprite.h"
#include <string>
namespace Engine {
    class Player {
    public:
        static Player* getInstance(std::string name, bool alive, int lives, DynamicSprite playerSprite);
        ~Player();
    protected:
        Player(std::string name, bool alive, int lives, DynamicSprite playerSprite);
    private:
        std::string name;
        bool alive;
        int lives;
        DynamicSprite playerSprite;
    };
}
#endif