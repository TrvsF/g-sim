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
	}

	void Controller::check_game_inputs()
	{
		if (m_input->KeyDown("w"))
		{
			std::cout << "w";
		}
	}

	void Controller::check_menu_inputs() {}

}