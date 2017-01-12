/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#include "STimer.h"

namespace Engine
{
	Uint32 STimer::getTimeElapsed()
	{
		Uint32 seconds = (Timer::getTimeElapsed() / 1000 );
		return seconds;
	}
}