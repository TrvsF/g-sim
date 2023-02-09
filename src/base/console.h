#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "../event/event.h"

#include <string>
#include <sstream>
#include <memory>

namespace console
{
	inline char m_inputstr[64] = "";

	inline bool SPECIAL = false;
	inline bool ACTIVE  = false;

	inline std::shared_ptr<_EventBus> bus = event::Event::SharedInstace().EventBus;

	void GetSubcommands(std::string command, int* subints, int arrsize);
	inline void GetSubcommands(std::string command, int* subints, int arrsize)
	{
		int counter = 0;
		std::string c(command);
		std::string buffer;
		std::stringstream stream(c);
		
		while (stream >> buffer && counter <= arrsize)
		{
			if (counter == 0) { counter++; continue; }
			subints[counter-1] = std::stoi(buffer);
			counter++;
		}
	}

	inline void InputChar(const char* c)
	{
		SPECIAL = false;
		if (strlen(m_inputstr) < 63)
		{
			strncat_s(m_inputstr, c, 1);
		}
	}

	inline void InputBackspace()
	{
		SPECIAL = false;
		size_t last = strlen(m_inputstr);
		if (last > 0)
		{
			m_inputstr[last - 1] = '\0';
		}
	}

	inline void InputEnter()
	{
		// console & refresh
		printf("\033[2J");
		printf("\033[%d;%dH", 0, 0);
		std::cout << ">/ " << m_inputstr << "\n";

		// coammnds
		std::string input   = std::string(m_inputstr);
		std::string command = input.substr(0, input.find(" "));

		// - tp
		if (command == "tp" || command == "pos")
		{
			int newpos[2];
			int size = sizeof(newpos) / sizeof(newpos[0]);
			GetSubcommands(input, newpos, size);

			float x = (float)newpos[0];
			float y = (float)newpos[1];

			bus->postpone(event::ePosChange { Vector2D{x, y} });
			bus->process();

			SPECIAL = true;
		}

		// - scale
		if (command == "scale")
		{
			int newscale[1];
			int size = sizeof(newscale) / sizeof(newscale[0]);
			GetSubcommands(input, newscale, size);

			// TODO : set render scale to newscale[0]

			SPECIAL = true;
		}

		m_inputstr[0] = '\0';
	}
}
#endif // !CONSOLE_H_