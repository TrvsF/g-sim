#ifndef UPDATER_H_
#define UPDATER_H_

#include "../engine/helper_macos.h"

#include "../input/input.h"

namespace updater
{
	class Updater
	{
	private:
		static Updater* s_instance;

	public:
		Updater();
		virtual ~Updater();

		static void Create();
		static Updater* Get();
		static void Destroy();

		void Tick();
	};
}

#endif