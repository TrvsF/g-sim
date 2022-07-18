#ifndef INPUT_H_
#define INPUT_H_

#include <SDL.h>

#include "../src/engine/helper_macos.h"

namespace input
{
	enum class MouseButton
	{
		Left,
		Right,
		Middle,
		Back,
		Forward
	};

	class Input
	{
	private:
		static Input* s_instance;

		const Uint8* m_keyboard_states;
		Uint8* m_prev_keyboard_states;
		int m_key_length;

		Uint32 m_mouse_state;
		Uint32 m_prev_mouse_state;
		int m_mouse_x;
		int m_mouse_y;

		void CopyToPrev();

	public:
		Input();
		virtual ~Input();

		static void Create();
		static Input* Get();
		static void Destroy();

		bool KeyDown(SDL_Scancode scan_code);
		bool KeyPressed(SDL_Scancode scan_code);
		bool KeyReleased(SDL_Scancode scan_code);

		bool MouseDown(MouseButton mouse_button);
		bool MousePressed(MouseButton mouse_button);
		bool MouseReleased(MouseButton mouse_button);

		void Tick();
		void LateTick();

	};
}

#endif