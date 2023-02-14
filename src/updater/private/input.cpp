#include "../input.h"

namespace updater
{
	Input::Input()
	{
		m_keyboard_states = SDL_GetKeyboardState(&m_key_length);
		m_prev_keyboard_states = new Uint8[m_key_length];
		LateTick();
	}

	Input::~Input()
	{
	}

	bool Input::KeyDown(const char* key)
	{
		SDL_Scancode scan_code = SDL_GetScancodeFromName(key);
		
		return m_keyboard_states[scan_code] != 0 && check_scancode(scan_code);
	}

	bool Input::KeyPressed(const char* key)
	{
		SDL_Scancode scan_code = SDL_GetScancodeFromName(key);

		return m_prev_keyboard_states[scan_code] == 0 && m_keyboard_states[scan_code] != 0 && check_scancode(scan_code);
	}

	bool Input::KeyReleased(const char* key)
	{
		SDL_Scancode scan_code = SDL_GetScancodeFromName(key);

		return m_prev_keyboard_states[scan_code] != 0 && m_keyboard_states[scan_code] == 0 && check_scancode(scan_code);
	}

	bool Input::KeyDown(int scancode)
	{
		if (scancode < 4 || scancode > 44) { return false; }

		return m_keyboard_states[scancode] != 0;
	}

	bool Input::KeyPressed(int scancode)
	{
		if (scancode < 4 || scancode > 44) { return false; }

		return m_prev_keyboard_states[scancode] == 0 && m_keyboard_states[scancode] != 0;
	}

	bool Input::KeyReleased(int scancode)
	{
		if (scancode < 4 || scancode > 44) { return false; }

		return m_prev_keyboard_states[scancode] != 0 && m_keyboard_states[scancode] == 0;
	}

	const char* Input::CharFromScancode(int scancode)
	{
		return &m_sdlmap[scancode];
	}

	bool Input::MouseDown(MouseButton mouse_button, int& x, int& y)
	{
		x = m_mouse_x;
		y = m_mouse_y;
		return (((int)m_mouse_state & mouse_button) != 0);
	}

	bool Input::MousePressed(MouseButton mouse_button, int& x, int& y)
	{
		x = m_mouse_x;
		y = m_mouse_y;
		return (((int)m_prev_mouse_state & mouse_button) == 0) && (((int)m_mouse_state & mouse_button) != 0);
	}

	bool Input::MouseReleased(MouseButton mouse_button, int& x, int& y)
	{
		x = m_mouse_x;
		y = m_mouse_y;
		return (((int)m_prev_mouse_state & mouse_button) != 0) && (((int)m_mouse_state & mouse_button) == 0);
	}

	void Input::LateTick()
	{
		// copy current values to be used next tick
		SDL_memcpy(m_prev_keyboard_states, m_keyboard_states, m_key_length);
		m_prev_mouse_state = m_mouse_state;
	}

	void Input::Tick()
	{
		m_mouse_state = SDL_GetMouseState(&m_mouse_x, &m_mouse_y);
	}

	bool Input::check_scancode(SDL_Scancode scan_code)
	{
		return !(scan_code == SDL_SCANCODE_UNKNOWN);
	}
}