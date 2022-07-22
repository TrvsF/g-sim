#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream> // remove me

#include "../src/updater/input.h"

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
		ControllerState m_current_controller;

		updater::Input* m_input;

		void check_menu_inputs();
		void check_game_inputs();

	public:
		Controller();

		inline void CheckInputs();
	};
}

#include "controller-inl.h"

#endif