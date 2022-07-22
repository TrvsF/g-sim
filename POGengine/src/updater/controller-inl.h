#include "controller.h"

namespace updater
{
	inline void Controller::CheckInputs()
	{
		if (m_current_controller == ControllerState::Game)
		{
			check_game_inputs();
		}

		if (m_current_controller == ControllerState::Menu)
		{
			check_menu_inputs();
		}
	}
}