#include "../controller.h"

namespace updater
{
	/*
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
	*/

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
		if (m_input->KeyDown("w"))
		{
			std::cout << "w";
		}
		m_player->Forward = m_input->KeyDown("w");
	}

	void Controller::check_menu_inputs() {}

}