#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream> // remove me

#include "../src/input/input.h"

namespace controller
{
	enum class CurrentController
	{
		Menu,
		Game
	};

	class Controller
	{
	private:
		static Controller* s_instance;

		CurrentController m_current_controller;

		input::Input* m_input;

		void check_menu_inputs();
		void check_game_inputs();

	public:
		Controller();
		virtual ~Controller();

		static void Create();
		static inline Controller* Get();
		static void Destroy();

		void CheckInputs();
	};
}

#include "controller-inl.h"

#endif