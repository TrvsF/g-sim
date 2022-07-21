#include "controller.h"

namespace controller
{
	inline Controller* Controller::Get()
	{
		return Controller::s_instance;
	}
}