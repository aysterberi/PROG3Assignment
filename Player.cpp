#include <string>
#include "Player.h"


namespace Engine {

    Player::Player(std::string name, bool alive, int lives, DynamicSprite playerSprite):
        name(name), alive(alive), lives(lives), playerSprite(playerSprite) {
    }

    Player* Player::getInstance(std::string name, bool alive, int lives, DynamicSprite playerSprite)
    {
        return nullptr;
    }

    Player::~Player()
    {
    }
}
