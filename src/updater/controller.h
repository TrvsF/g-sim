#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream> // remove me

#include "../game/game.h"
#include "input.h"

namespace updater
{
	enum class ControllerState
	{
		Menu,
		Game
	};

	class Controller
	{
	private:
		ControllerState m_controller_state;

		object::Player*		m_player;
		Input*				m_input;

		void check_menu_inputs();
		void check_game_inputs();
		void global_checks();

	public:
		Controller(Input* input);

		inline void SetPlayer(object::Player* player);

		inline void CheckInputs();
	};
}

#include "controller-inl.h"

#endif