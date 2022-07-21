#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <SDL.h>

#include "../renderer/renderer.h"
#include "../physics/updater.h"
#include "../input/input.h"
#include "../controller/controller.h"

#include "../util/timer.h"

#include "../object/component/texture.h"

namespace base
{
	bool Init();
	void Run();
	void Stop();
}

#endif // ENGINE_H_