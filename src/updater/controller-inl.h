#include "controller.h"

namespace updater
{
	inline void Controller::CheckInputs()
	{
		if (m_controller_state == ControllerState::Game)
		{
			check_game_inputs();
		}

		if (m_controller_state == ControllerState::Menu)
		{
			check_menu_inputs();
		}
	}

	inline void Controller::SetPlayer(object::GameObject* player)
	{
		m_player = player;
	}
}