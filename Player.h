#ifndef PLAYER_H
#define PLAYER_H
#include "DynamicSprite.h"
class Player
{
public:
    static Player* getInstance();
    ~Player();
protected:
    Player();
private:
    bool alive;
    int lives;
    DynamicSprite DynamicSprite::playerSprite;
};

#endif