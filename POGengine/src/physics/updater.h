#ifndef UPDATER_H_
#define UPDATER_H_

#include "../engine/helper_macos.h"

#include "../input/input.h"

namespace physics
{
	class Updater
	{
	private:
		static Updater* s_instance;

	public:
		Updater();
		virtual ~Updater();

		static void Create();
		static inline Updater* Get();
		static void Destroy();

		void Tick();
	};
}

#include "updater-inl.h"

#endif