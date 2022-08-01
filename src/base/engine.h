#ifndef ENGINE_H_
#define ENGINE_H_

#include <SDL.h>

#include "../renderer/renderer.h"
#include "../updater/updater.h"
#include "../game/game.h"
#include "../util/timer.h"

namespace base
{
	bool Init();
	void Run();
	void Stop();
}

#endif // ENGINE_H_