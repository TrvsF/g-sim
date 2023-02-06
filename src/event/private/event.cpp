#include "../event.h"

namespace event
{
	Event::Event()
	{
		EventBus = std::make_shared<_EventBus>();
	}
}