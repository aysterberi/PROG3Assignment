#include "KeyHandler.h"
#include <unordered_map>
namespace Engine {
	std::unordered_map<SDL_Keycode, std::vector<KeyHandler::FunctionHook>> function_map;

	KeyHandler::KeyHandler()
	{
	}


	KeyHandler::~KeyHandler()
	{
	}

	void KeyHandler::notify(SDL_KeyboardEvent &event)
	{

	}


	void KeyHandler::hook(FunctionHook function, SDL_Keycode keycode)
	{
		std::vector<FunctionHook> func_vect = function_map[keycode];
		func_vect.push_back(function);
	}

}
