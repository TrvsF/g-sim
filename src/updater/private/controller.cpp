#include "../controller.h"

namespace updater
{
	Controller::Controller(Input* input)
	{
		m_controller_state	= ControllerState::Game;
		m_input				= input;
		m_player			= nullptr;
	}

	void Controller::check_game_inputs()
	{
		if (m_player == nullptr) 
		{ 
			m_player = game::Game::Get()->GetPlayer();
		}
		m_player->Forward = m_input->KeyDown("w");
		m_player->Backward = m_input->KeyDown("s");
	}

	void Controller::check_menu_inputs() {}
}