#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>

namespace game
{
	// private var (promise)
	std::string m_inputstr;

	bool ACTIVE;

	void InputChar(const char* c)
	{
		m_inputstr.append(c);
	}

	void InputBackspace()
	{
		if (m_inputstr.length() > 0)
		{
			m_inputstr.pop_back();
		}
	}

	void InputEnter();
}

#endif // !CONSOLE_H_