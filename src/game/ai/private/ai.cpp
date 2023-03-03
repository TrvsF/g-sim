#include "../ai.h"

namespace ai
{
	AI::AI()
	{
		m_listener.listen<event::eObjectDeath>(std::bind(&AI::e_objectdeath, this, std::placeholders::_1));
		m_listener.listen<event::eAgentBorn> (std::bind(&AI::e_agentborn,  this, std::placeholders::_1));
	}

	void AI::e_objectdeath(const event::eObjectDeath& event)
	{
		// do_debugconsole();
	}

	void AI::e_agentborn(const event::eAgentBorn& event)
	{
		// do_debugconsole();
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
		std::cout
			<< std::left << std::setfill(' ') << std::setw(24) << "name"  << " "
			<< std::left << std::setfill(' ') << std::setw(12) << "state" << " "
			<< std::left << std::setfill(' ') << std::setw(4)  << "hp"    << " "
			<< std::left << std::setfill(' ') << std::setw(5)  << "stamina" << "\n";
		for (const auto& agent : getagents())
		{
			std::cout
				<< std::left << std::setfill(' ') << std::setw(24) << agent->GetName()		<< " "
				<< std::left << std::setfill(' ') << std::setw(12) << agent->GetStateStr()	<< " "
				<< std::left << std::setfill(' ') << std::setw(4)  << agent->GetHealth()	<< " "
				<< std::left << std::setfill(' ') << std::setw(5)  << agent->GetStamina()	<<
			"\n";
		}
	}

	void AI::Tick()
	{
		m_tickcounter++;
		if (m_tickcounter % 64 == 0)
		{
			do_debugconsole();
		}
	}
}