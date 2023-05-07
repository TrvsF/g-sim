#include "../ai.h"

namespace ai
{
	AI::AI()
	{
		m_listener.listen<event::eObjectDeath>(std::bind(&AI::e_objectdeath, this, std::placeholders::_1));
		m_listener.listen<event::eAgentSpawn>(std::bind(&AI::e_agentspawn, this, std::placeholders::_1));

		m_tick_counter = 0;
		m_agentid_counter = 0;

		// logs
		file::CreateLogFile();
	}

	void AI::e_objectdeath(const event::eObjectDeath& event)
	{
		if (event.victim->GetEntityType() == object::GameEntityType::Food)
		{ return; }

		const auto& agent = static_cast<object::Agent*>(event.victim);
		std::string id    = std::to_string(agent->Id());
		std::string tick  = std::to_string(m_tick_counter);

		std::string line = "DEATH:" + id + ":" + tick;
		file::AppendLogFile(line);

		std::string age = std::to_string(agent->GetAge());

		std::string data = age;
		file::AppendAgentFile(id, data);
	}

	void AI::e_agentspawn(const event::eAgentSpawn& event)
	{
		m_agentid_counter++;

		const auto& agent = static_cast<object::Agent*>(event.agent);
		agent->Id(m_agentid_counter);
		std::string id    = std::to_string(m_agentid_counter);
		std::string tick  = std::to_string(m_tick_counter);

		std::string line = "BIRTH:" + id + ":" + tick;
		file::AppendLogFile(line);

		auto r = std::to_string(agent->Colour().r) + ",";
		auto g = std::to_string(agent->Colour().g) + ",";
		auto b = std::to_string(agent->Colour().b);

		std::string tris;
		for (const auto& tri : agent->GetGeometry()->Tris())
		{
			auto point = tri.GetPoint1();
			auto px = std::to_string(point.x);
			auto py = std::to_string(point.y);
			tris += "(" + px + "," + py + ")";
		}

		std::string name   = agent->GetName();
		std::string colour = r + g + b;
		
		std::string data = name + ":" + colour + ":" + tris + ":";
		file::CreateAgentFile(id, data);
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
		m_tick_counter++;
		if (m_tick_counter % 32 == 0)
		{
			do_debugconsole();
		}
	}
}