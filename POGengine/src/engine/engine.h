#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <SDL.h>

#include "../renderer/renderer.h"
#include "../physics/updater.h"
#include "../input/input.h"

#include "../util/timer.h"

#include "../object/component/texture.h"

namespace engine
{
	bool Init();
	void Run();
	void Stop();
}

#endif // ENGINE_H_