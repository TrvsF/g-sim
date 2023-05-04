#include "../ai.h"

namespace ai
{
	AI::AI()
	{
		// logs
		file::CreateLogFile();

		m_listener.listen<event::eObjectDeath>(std::bind(&AI::e_objectdeath, this, std::placeholders::_1));
		m_listener.listen<event::eAgentSpawn> (std::bind(&AI::e_agentspawn,  this, std::placeholders::_1));
		m_tickcounter = 0;
	}

	void AI::e_objectdeath(const event::eObjectDeath& event)
	{
		std::string name = static_cast<object::Agent*>(event.victim)->GetName();
		std::string data = "DEATH " + name + " " + std::to_string(m_tickcounter);
		file::AppendToLogFile(data);
	}

	void AI::e_agentspawn(const event::eAgentSpawn& event)
	{
		std::string name = static_cast<object::Agent*>(event.agent)->GetName();
		std::string data = "BRITH " + name + " " + std::to_string(m_tickcounter);
		file::AppendToLogFile(data);
	}

	std::vector<object::Agent*> AI::get_agents()
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
			<< std::left << std::setfill(' ') << std::setw(24) << "name"    << " "
			<< std::left << std::setfill(' ') << std::setw(12) << "state"   << " "
			<< std::right<< std::setfill(' ') << std::setw(3)  << "hp"      << "/"
			<< std::left << std::setfill(' ') << std::setw(5)  << "max"		<< " "
			<< std::right<< std::setfill(' ') << std::setw(5)  << "stamina" << "/"
			<< std::left << std::setfill(' ') << std::setw(5)  << "max"		<< 
		"\n";

		for (const auto& agent : get_agents())
		{
			std::cout
				<< std::left << std::setfill(' ') << std::setw(24) << agent->GetName()		 << " "
				<< std::left << std::setfill(' ') << std::setw(12) << agent->GetStateStr()	 << " "
				<< std::right<< std::setfill(' ') << std::setw(3)  << agent->GetHealth()	 << "/"
				<< std::left << std::setfill(' ') << std::setw(5)  << agent->GetMaxHealth()  << " "
				<< std::right<< std::setfill(' ') << std::setw(6)  << agent->GetStamina()	 << "/"
				<< std::left << std::setfill(' ') << std::setw(5)  << agent->GetMaxStamina() <<
			"\n";
		}
	}

	void AI::Tick()
	{
		m_tickcounter++;
		if (m_tickcounter % 32 == 0)
		{
			do_debugconsole();
		}
	}
}