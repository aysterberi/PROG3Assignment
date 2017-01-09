#include "STimer.h"

namespace Engine
{
	Uint32 STimer::getTimeElapsed()
	{
		Uint32 seconds = (Timer::getTimeElapsed() / 1000 );
		return seconds;
	}
}