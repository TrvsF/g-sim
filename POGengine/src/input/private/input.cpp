#include "../input.h"

namespace input
{
	Input* Input::s_instance = nullptr;

	Input::Input()
	{
		m_keyboard_states = SDL_GetKeyboardState(&m_key_length);
		m_prev_keyboard_states = new Uint8[m_key_length];
		LateTick();
	}

	Input::~Input()
	{
	}

	void Input::Create()
	{
		if (!s_instance)
		{
			s_instance = new Input();
		}
	}
	
	Input* Input::Get()
	{
		return Input::s_instance;
	}

	void Input::Destroy()
	{
		SAFE_DELETE(s_instance);
	}

	bool Input::KeyDown(const char* key)
	{
		SDL_Scancode scan_code = SDL_GetScancodeFromName(key);
		
		return m_keyboard_states[scan_code] && check_scancode(scan_code);
	}

	bool Input::KeyPressed(const char* key)
	{
		SDL_Scancode scan_code = SDL_GetScancodeFromName(key);

		return (m_prev_keyboard_states[scan_code]) == 0 && (m_keyboard_states[scan_code] != 0) && check_scancode(scan_code);
	}

	bool Input::KeyReleased(const char* key)
	{
		SDL_Scancode scan_code = SDL_GetScancodeFromName(key);

		return (m_prev_keyboard_states[scan_code]) != 0 && (m_keyboard_states[scan_code] == 0) && check_scancode(scan_code);
	}

	bool Input::MouseDown(MouseButton mouse_button)
	{
		return ((m_mouse_state & mouse_button) != 0);
	}

	bool Input::MousePressed(MouseButton mouse_button)
	{
		return ((m_prev_mouse_state & mouse_button) == 0) && ((m_mouse_state & mouse_button) != 0);
	}

	bool Input::MouseReleased(MouseButton mouse_button)
	{
		return ((m_prev_mouse_state & mouse_button) != 0) && ((m_mouse_state & mouse_button) == 0);
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
