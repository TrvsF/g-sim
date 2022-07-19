#include "../updater.h"

namespace updater
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

	Updater* Updater::Get()
	{
		return Updater::s_instance;
	}

	void Updater::Destroy()
	{
		SAFE_DELETE(s_instance);
	}

	void Updater::Tick()
	{

	}

}