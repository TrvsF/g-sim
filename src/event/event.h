#ifndef EVENT_H_
#define EVENT_H_

#include <dexode/EventBus.hpp>

#include "../util/vector2d.h"

#include <iostream>

using _EventBus = dexode::EventBus;
using _Listener = dexode::EventBus::Listener;

namespace event
{
	// events
	struct ePosChange
	{
		Vector2D pos;
	};

	class Event
	{
	private:
		Event();
		virtual ~Event() = default;

	public:
		std::shared_ptr<_EventBus> EventBus;
		static Event& SharedInstace() { static Event event; return event; }
	};
}

#endif