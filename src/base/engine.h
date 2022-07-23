#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream> // delete me
#include <SDL.h>

#include "../renderer/renderer.h"
#include "../updater/updater.h"
#include "../game/game.h"
#include "../util/timer.h"

#include "../game/object/component/texture.h" // delete me

namespace base
{
	bool Init();
	void Run();
	void Stop();
}

#endif // ENGINE_H_