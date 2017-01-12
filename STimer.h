/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#ifndef STIMER_H
#define STIMER_H

#include "Timer.h"

namespace Engine {

	class STimer : public Timer {
	public:
		using Timer::Timer;
		Uint32 getTimeElapsed() override;
	private:

	};
}
#endif

