#include "../ai.h"

namespace ai
{
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
			std::cout << agent->GetName() << "\n";
		}
	}

	void AI::Tick()
	{
		do_debugconsole();
	}
}