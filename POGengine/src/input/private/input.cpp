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

	bool Input::KeyDown(SDL_Scancode scan_code)
	{
		return m_keyboard_states[scan_code];
	}

	bool Input::KeyPressed(SDL_Scancode scan_code)
	{
		return (m_prev_keyboard_states[scan_code]) == 0 && (m_keyboard_states[scan_code] != 0);
	}

	bool Input::KeyReleased(SDL_Scancode scan_code)
	{
		return (m_prev_keyboard_states[scan_code]) != 0 && (m_keyboard_states[scan_code] == 0);
	}

	bool Input::MouseDown(MouseButton mouse_button)
	{
		Uint32 mask = 0;

		switch (mouse_button) {
		case MouseButton::Left:
			mask = SDL_BUTTON_LMASK;
			break;
		case MouseButton::Right:
			mask = SDL_BUTTON_RMASK;
			break;
		case MouseButton::Middle:
			mask = SDL_BUTTON_MMASK;
			break;
		case MouseButton::Back:
			mask = SDL_BUTTON_X1MASK;
			break;
		case MouseButton::Forward:
			mask = SDL_BUTTON_X2MASK;
			break;
		}

		return ((m_mouse_state & mask) != 0);
	}

	bool Input::MousePressed(MouseButton mouse_button)
	{
		Uint32 mask = 0;

		switch (mouse_button) {
		case MouseButton::Left:
			mask = SDL_BUTTON_LMASK;
			break;
		case MouseButton::Right:
			mask = SDL_BUTTON_RMASK;
			break;
		case MouseButton::Middle:
			mask = SDL_BUTTON_MMASK;
			break;
		case MouseButton::Back:
			mask = SDL_BUTTON_X1MASK;
			break;
		case MouseButton::Forward:
			mask = SDL_BUTTON_X2MASK;
			break;
		}

		return ((m_prev_mouse_state & mask) == 0) && ((m_mouse_state & mask) != 0);
	}

	bool Input::MouseReleased(MouseButton mouse_button)
	{
		Uint32 mask = 0;

		switch (mouse_button) {
		case MouseButton::Left:
			mask = SDL_BUTTON_LMASK;
			break;
		case MouseButton::Right:
			mask = SDL_BUTTON_RMASK;
			break;
		case MouseButton::Middle:
			mask = SDL_BUTTON_MMASK;
			break;
		case MouseButton::Back:
			mask = SDL_BUTTON_X1MASK;
			break;
		case MouseButton::Forward:
			mask = SDL_BUTTON_X2MASK;
			break;
		}

		return ((m_prev_mouse_state & mask) != 0) && ((m_mouse_state & mask) == 0);
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

}
