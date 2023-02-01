#ifndef INPUT_H_
#define INPUT_H_

#include <SDL.h>
#include <iostream>
#include <unordered_map>

#include "../src/base/helper_macos.h"

namespace updater
{
	enum MouseButton
	{
		Left = 1,
		Middle = 2,
		Right = 4,
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
		int m_mouse_x = 0;
		int m_mouse_y = 0;

		std::unordered_map<int, const char> m_sdlmap =
		{
			{4, 'a'},
			{5, 'b'},
			{6, 'c'},
			{7, 'd'},
			{8, 'e'},
			{9, 'f'},
			{10, 'g'},
			{11, 'h'},
			{12, 'i'},
			{13, 'j'},
			{14, 'k'},
			{15, 'l'},
			{16, 'm'},
			{17, 'n'},
			{18, 'o'},
			{19, 'p'},
			{20, 'q'},
			{21, 'r'},
			{22, 's'},
			{23, 't'},
			{24, 'u'},
			{25, 'v'},
			{26, 'w'},
			{27, 'x'},
			{28, 'y'},
			{29, 'z'},
			{30, '1'},
			{31, '2'},
			{32, '3'},
			{33, '4'},
			{34, '5'},
			{35, '6'},
			{36, '7'},
			{37, '8'},
			{38, '9'},
			{39, '0'},
			{44, ' '}
		};

		bool check_scancode(SDL_Scancode scan_code);

	public:
		Input();
		virtual ~Input();

		bool KeyDown(const char* key);
		bool KeyPressed(const char* key);
		bool KeyReleased(const char* key);

		// this is stupid!
		bool KeyDown(int scancode);
		bool KeyPressed(int scancode);
		bool KeyReleased(int scancode);

		const char* CharFromScancode(int scancode);

		bool MouseDown(MouseButton mouse_button, int& x, int& y);
		bool MousePressed(MouseButton mouse_button, int& x, int& y);
		bool MouseReleased(MouseButton mouse_button, int& x, int& y);

		void Tick();
		void LateTick();

	};
}

#endif