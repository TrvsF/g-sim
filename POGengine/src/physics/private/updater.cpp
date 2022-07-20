#include "../updater.h"

namespace physics
{
	Updater* Updater::s_instance = nullptr;

	Updater::Updater()
	{
	}

	Updater::~Updater()
	{
	}

	void Updater::Create()
	{
		if (!Updater::s_instance)
		{
			Updater::s_instance = new Updater();
		}
	}

	void Updater::Destroy()
	{
		SAFE_DELETE(s_instance);
	}

	void Updater::Tick()
	{
		
	}

}