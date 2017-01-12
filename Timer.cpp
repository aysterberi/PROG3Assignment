/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#include "Timer.h"
#include <SDL.h>

/*
 * This class is based on the example
 * by Lazy Foo for a simple Timer.
 */
namespace Engine
{

	Timer::Timer() : startTicks(0), pausedTicks(0), paused(false), started(false)
	{
	}

	void Timer::start()
	{
		started = true;
		//unpause and reset pause tick counter
		paused = false;
		pausedTicks = 0;

		//get time from SDL
		startTicks = SDL_GetTicks();


	}

	void Timer::stop()
	{
		//we're no longer running
		started = false;
		startTicks = 0;

		//nor are we paused
		paused = false;
		pausedTicks = 0;
	}

	void Timer::pause()
	{
		//if we're running
		if (started && !paused)
		{
			paused = true;
		}

		//take a snapshot of current time
		pausedTicks = SDL_GetTicks() - startTicks;

		//reset start timer
		startTicks = 0;
	}

	void Timer::unpause()
	{
		if (started && paused)
		{
			paused = false;
		}

		//correct for relative time, i.e. timer time
		startTicks = SDL_GetTicks() - pausedTicks;

		//reset paused time tracker
		pausedTicks = 0;
	}

	Uint32 Timer::getTimeElapsed()
	{
		//ret val
		Uint32 time = 0;

		if (started)
		{
			//if paused, return that time
			if (paused)
			{
				time = pausedTicks;
			}
			else
			{
				//return actual time
				time = SDL_GetTicks() - startTicks;
			}
		}

		return time;
	}

	bool Timer::isStarted() const
	{
		return started;
	}
	bool Timer::isPaused() const
	{
		//we can only be paused if we have
		//started counting
		return paused && started;
	}

}
