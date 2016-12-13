#ifndef KEYHANDLER_H
#define  KEYHANDLER_H
#include "GameObject.h"
#include <vector>
#include <functional>
#include <unordered_map>

namespace Engine {
	class KeyHandler
	{
	public:
		typedef std::vector<SDL_Keycode> KeyVector;
		typedef std::function<void()> FunctionHook;
		KeyHandler();
		~KeyHandler();
		void notify(SDL_Keycode keycode);
		void hook(FunctionHook func, SDL_Keycode keycode);
		void unhook(FunctionHook func, SDL_Keycode keycode);

	private:
		std::unordered_map<SDL_Keycode, std::vector<FunctionHook>> KeyHandler::function_map;
	};
}
#endif

