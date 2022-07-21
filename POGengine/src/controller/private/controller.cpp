#include "../controller.h"

namespace controller
{
	Controller* Controller::s_instance = nullptr;

	Controller::Controller()
	{
		m_current_controller = CurrentController::Game;
	}

	Controller::~Controller()
	{
	}

	void Controller::Create()
	{
		if (!s_instance)
		{
			s_instance = new Controller();
		}
	}

	void Controller::Destroy()
	{
	}

	void Controller::CheckInputs()
	{
		if (m_current_controller == CurrentController::Game)
		{
			check_game_inputs();
		}

		if (m_current_controller == CurrentController::Menu)
		{
			check_menu_inputs();
		}
	}

	void Controller::check_game_inputs()
	{
		input::Input* input = m_input->Get();
		
		if (input->KeyDown("w"))
		{
			std::cout << "DOUBLE U\n";
		}
	}

	void Controller::check_menu_inputs() {}

}