#ifndef EVENT_H_
#define EVENT_H_

#include <dexode/EventBus.hpp>

#include "../game/world/game-object.h"
#include "../util/vector2d.h"

#include <iostream>

using _EventBus = dexode::EventBus;
using _Listener = dexode::EventBus::Listener;

namespace event
{
	// EVENTS
	// commands
	struct ePosChange
	{
		Vector2D pos;
	};
	struct eScaleChange
	{
		float scale;
	};
	// agents
	struct eObjectDeath
	{
		object::GameObject* victim;
		// object::GameObject* killer;
	};

	struct eAgentBorn
	{
		object::GameObject* agent;
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