#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>

namespace console
{
	// private var (promise)
	inline std::string m_inputstr = "";

	inline bool ACTIVE = false;

	inline void InputChar(const char* c)
	{
		m_inputstr.append(c);
	}

	inline void InputBackspace()
	{
		if (m_inputstr.length() > 0)
		{
			m_inputstr.pop_back();
		}
	}

	inline void InputEnter();
}

#endif // !CONSOLE_H_