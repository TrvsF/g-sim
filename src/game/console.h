#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>

namespace console
{
	// private var (promise)
	inline char m_inputstr[32] = "";

	inline bool ACTIVE = false;

	inline void InputChar(const char* c)
	{
		if (strlen(m_inputstr) < 30)
		{ 
			strncat(m_inputstr, c, 1);
		}
	}

	inline void InputBackspace()
	{
		int last = strlen(m_inputstr);
		if (last > 0)
		{
			m_inputstr[last - 1] = '\0';
		}
	}

	inline void InputEnter()
	{
		printf(m_inputstr);
		m_inputstr[0] = '\0';
	}
}

#endif // !CONSOLE_H_