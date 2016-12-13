#include "KeyHandler.h"
#include <unordered_map>
namespace Engine {
	KeyHandler::KeyHandler()
	{
	}


	KeyHandler::~KeyHandler()
	{
	}

	void KeyHandler::notify(SDL_Keycode keycode)
	{
		std::vector<FunctionHook> func_vect = function_map[keycode];
		for (auto& function : func_vect)
		{
			function();
		}

	}

	
	void KeyHandler::hook(FunctionHook function, SDL_Keycode keycode)
	{
		std::vector<FunctionHook> func_vect = function_map[keycode];
		func_vect.push_back(function);
	}

	void KeyHandler::unhook(FunctionHook func, SDL_Keycode keycode)
	{
		std::vector<FunctionHook> func_vect = function_map[keycode];
	}

}
