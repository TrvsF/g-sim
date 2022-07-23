#ifndef INPUT_H_
#define INPUT_H_

#include <SDL.h>
#include <iostream>

#include "../src/base/helper_macos.h"

namespace updater
{
	enum MouseButton
	{
		Left = 1,
		Right = 2,
		Middle = 4,
		Back = 8,
		Forward = 16
	};

	class Input
	{
	private:
		const Uint8* m_keyboard_states;
		Uint8* m_prev_keyboard_states;
		int m_key_length;

		Uint32 m_mouse_state;
		Uint32 m_prev_mouse_state;
		int m_mouse_x;
		int m_mouse_y;

		bool check_scancode(SDL_Scancode scan_code);

	public:
		Input();
		virtual ~Input();

		bool KeyDown(const char* key);
		bool KeyPressed(const char* key);
		bool KeyReleased(const char* key);

		bool MouseDown(MouseButton mouse_button);
		bool MousePressed(MouseButton mouse_button);
		bool MouseReleased(MouseButton mouse_button);

		void Tick();
		void LateTick();

	};
}

#endif