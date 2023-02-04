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

	void Updater::Tick()
	{
		// must be first
		m_input->Tick();
		m_controller->CheckInputs();
		
		// must be last
		m_input->LateTick();
	}

}