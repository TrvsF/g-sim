#ifndef UPDATER_H_
#define UPDATER_H_

#include <iostream> // delete me
#include <vector>

#include "../base/helper_macos.h"
#include "../game/object/game/game-object.h"
#include "controller.h"
#include "input.h"

namespace updater
{
	class Updater
	{
	private:
		static Updater* s_instance;

		Controller* m_controller;
		Input*		m_input;

		Updater();
	public:
		static void Create();
		static inline Updater* Get();
		static void Destroy();

		void Tick();
	};
}

#include "updater-inl.h"

#endif