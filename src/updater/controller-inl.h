#include "controller.h"

namespace updater
{
	inline void Controller::CheckInputs()
	{
		global_checks();

		if (m_controller_state == ControllerState::Game)
		{
			check_game_inputs();
		}

		if (m_controller_state == ControllerState::Menu)
		{
			check_menu_inputs();
		}
	}

	inline void Controller::SetPlayer(object::Player* player)
	{
		m_player = player;
	}
}