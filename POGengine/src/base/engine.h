#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <SDL.h>

#include "../renderer/renderer.h"
#include "../updater/updater.h"
#include "../updater/input.h"
#include "../updater/controller.h"

#include "../util/timer.h"

#include "../game/object/component/texture.h"

namespace base
{
	bool Init();
	void Run();
	void Stop();
}

#endif // ENGINE_H_