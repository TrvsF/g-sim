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
	// ---------------------
	// misc
	struct ePosChange
	{
		Vector2D pos;
	};
	struct eScaleChange
	{
		float scale;
	};
	struct eSetDrawAABB
	{
		bool flag;
	};
	// agents
	struct eObjectDeath
	{
		object::GameObject* victim;
		// object::GameObject* killer;
	};
	struct eAgentBorn
	{
		Vector2D pos;

		std::string g1;
		std::string g2;
	};
	// ---------------------
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