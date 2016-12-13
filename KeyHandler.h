#ifndef KEYHANDLER_H
#define  KEYHANDLER_H
#include "GameObject.h"
#include <vector>
#include <functional>
namespace Engine {
	class KeyHandler
	{
	public:
		typedef std::vector<SDL_Keycode> KeyVector;
		typedef std::function<void()> FunctionHook;
		KeyHandler();
		~KeyHandler();
		void notify(SDL_KeyboardEvent &event);
		void hook(FunctionHook func, SDL_Keycode);
		void hook(FunctionHook func, KeyVector keys);
		void unhook(FunctionHook func, SDL_Keycode key);
		void unhook(FunctionHook func, KeyVector keys);
	};
}
#endif

