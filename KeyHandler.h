#ifndef KEYHANDLER_H
#define  KEYHANDLER_H
#include "GameObject.h"
#include <vector>

class KeyHandler
{
public:
	typedef std::vector<SDL_Keycode> KeyVector;
	KeyHandler();
	~KeyHandler();
	void notify(SDL_KeyboardEvent &event);
	void hook(Engine::GameObject &game_object, SDL_Keycode key);
	void hook(Engine::GameObject &game_object, KeyVector keys);
	void unhook(Engine::GameObject &game_object, SDL_Keycode key);
	void unhook(Engine::GameObject &game_object, KeyVector keys);
};
#endif

