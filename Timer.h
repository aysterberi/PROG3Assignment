#ifndef TIMER_H
#define TIMER_H
#include <SDL_stdinc.h>
namespace Engine
{

	class Timer
	{
	public:
		Timer();
		//use the default destructor
		//as the datatypes are trivial
		//c++11
		virtual ~Timer() = default;
		//clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//get time
		virtual Uint32 getTimeElapsed();

		//status checks
		bool isStarted() const;
		bool isPaused() const;

	private:
		//time at start() moment
		Uint32 startTicks;

		//time at pause() moment
		Uint32 pausedTicks;

		//status
		bool paused;
		bool started;
	};
}
#endif

