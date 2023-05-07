#ifndef AI_H_
#define AI_H_

#include "god.h"
#include "../game.h"
#include "../world/entities/agent.h"
#include "../world/game-object.h"

#include "../src/event/event.h"

#include <dexode/EventBus.hpp>
using Listener = dexode::EventBus::Listener;

namespace ai 
{
	class AI
	{
	private:
		AI();
		virtual ~AI() = default;

		Listener m_listener{ event::Event::SharedInstace().EventBus };
		void e_objectdeath(const event::eObjectDeath& event);
		void e_agentspawn (const event::eAgentSpawn& event);

		int m_agentid_counter;
		int m_tick_counter; // TODO : probably not a good idea

		std::vector<object::Agent*> get_agents();
		void do_debugconsole();
	public:
		static AI& SharedInstace() { static AI ai; return ai; }

		void Tick();
	};
}

#endif