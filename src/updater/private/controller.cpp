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
			m_player = game::Game::SharedInstace().GetPlayer();
		}

		if (m_input->KeyDown("w"))
		{ m_player->MoveUp(); }
		if (m_input->KeyDown("s"))
		{ m_player->MoveDown(); }
		if (m_input->KeyDown("a"))
		{ m_player->MoveLeft(); }
		if (m_input->KeyDown("d"))
		{ m_player->MoveRight(); }

		int x, y;
		if (m_input->MousePressed(Right, x, y))
		{
			game::Game::SharedInstace().MouseClick(Right, x, y);
		}
		if (m_input->MousePressed(Left, x, y))
		{
			game::Game::SharedInstace().MouseClick(Left, x, y);
		}
		// click & drag
		if (m_input->MouseDown(Left, x, y))
		{
			game::Game::SharedInstace().MouseDown(Left, x, y);
		}
		if (m_input->MouseDown(Back, x, y) || m_input->KeyDown("p"))
		{
			game::Game::SharedInstace().MouseDown(Back, x, y);
		}
		if (m_input->MouseDown(Forward, x, y) || m_input->KeyDown("o"))
		{
			game::Game::SharedInstace().MouseDown(Forward, x, y);
		}
		if (m_input->MouseReleased(Left, x, y))
		{
			game::Game::SharedInstace().MouseRelease(Left);
		}

		if (m_input->MouseReleased(Back, x, y))
		{
			//game::Game::SharedInstace().MouseDown(Back, x, y);
		}
		if (m_input->MouseReleased(Forward, x, y))
		{
			//game::Game::SharedInstace().MouseDown(Forward, x, y);
		}
	}

	void Controller::check_menu_inputs() {}

	void Controller::global_checks()
	{
		if (m_input->KeyPressed("`"))
		{
			console::ACTIVE = !console::ACTIVE;
		}

		if (console::ACTIVE)
		{
			// TODO : find a better way to get what keyboard keys are down (input.h)
			// alphabet
			for (int i = 4; i < 46; i++)
			{
				if (m_input->KeyPressed(i))
				{
					if (i >= 40 && i < 44) { continue; }
					const char* c = m_input->CharFromScancode(i);
					console::InputChar(c);
				}
			}
			// enter
			if (m_input->KeyPressed(40))
			{
				console::InputEnter();
			}
			// backspace
			if (m_input->KeyReleased(42))
			{
				console::InputBackspace();
			}
		}
	}
}