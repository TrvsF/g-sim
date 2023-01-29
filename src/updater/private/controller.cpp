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

		if (m_input->KeyDown("w"))
		{ m_player->MoveUp(); }
		if (m_input->KeyDown("s"))
		{ m_player->MoveDown(); }
		if (m_input->KeyDown("a"))
		{ m_player->MoveLeft(); }
		if (m_input->KeyDown("d"))
		{ m_player->MoveRight(); }

		if (m_input->MouseDown(Left))
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			game::Game::Get()->OnMouseClick(x, y, Left);
		}
		if (m_input->MousePressed(Right))
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			game::Game::Get()->OnMouseClick(x, y, Right);
		}

		if (m_input->MouseReleased(Left))
		{
			game::Game::Get()->OnMouseRelease(Left);
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
			for (int i = 4; i < 40; i++)
			{
				if (m_input->KeyPressed(i))
				{
					const char* c = m_input->CharFromScancode(i);
					console::InputChar(c);
				}
			}
			if (m_input->KeyPressed(44))
			{
				console::InputChar(" ");
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