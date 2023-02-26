#ifndef AI_H_
#define AI_H_

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
		void e_agentdeath(const event::eAgentDeath& event);
		void e_agentborn(const event::eAgentBorn& event);

		std::vector<object::Agent*> getagents();
		void do_debugconsole();
	public:
		static AI& SharedInstace() { static AI ai; return ai; }

		void Tick();
	};
}

#endif