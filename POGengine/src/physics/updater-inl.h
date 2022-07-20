#include "updater.h"

namespace physics
{
	inline Updater* Updater::Get()
	{
		return Updater::s_instance;
	}
}