#include "../ai.h"

namespace ai
{
	AI::AI()
	{
		m_listener.listen<event::eAgentDeath>(std::bind(&AI::e_agentdeath, this, std::placeholders::_1));
		m_listener.listen<event::eAgentBorn> (std::bind(&AI::e_agentborn,  this, std::placeholders::_1));
	}

	void AI::e_agentdeath(const event::eAgentDeath& event)
	{
		do_debugconsole();
	}

	void AI::e_agentborn(const event::eAgentBorn& event)
	{
		do_debugconsole();
	}

	std::vector<object::Agent*> AI::getagents()
	{
		std::vector <object::Agent*> agents;
		for (const auto& gameobject : game::Game::SharedInstace().GetGameObjects())
		{
			if (gameobject->GetEntityType() == object::GameEntityType::Agent)
			{
				agents.push_back(static_cast<object::Agent*> (gameobject));
			}
		}
		return agents;
	}

	void AI::do_debugconsole()
	{
		printf("\033[2J");
		printf("\033[%d;%dH", 0, 0);
		for (const auto& agent : getagents())
		{
			std::cout << agent->GetName() << " " << agent->GetHealth() << "\n";
		}
	}

	void AI::Tick()
	{
		
	}
}