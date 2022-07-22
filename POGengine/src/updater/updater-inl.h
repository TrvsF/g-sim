#include "updater.h"

namespace updater
{
	inline Updater* Updater::Get()
	{
		return Updater::s_instance;
	}
}