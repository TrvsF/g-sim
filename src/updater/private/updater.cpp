#include "../updater.h"

#include "../src/game/object/game-object.h"

namespace updater
{
	Updater* Updater::s_instance = nullptr;

	Updater::Updater()
	{
		m_input			= new Input();
		m_controller	= new Controller(m_input);
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
		// must be first
		m_input->Tick();
		m_controller->CheckInputs();

		/*
			keyboard updates wont work
		*/
		
		// must be last
		m_input->LateTick();
	}

}