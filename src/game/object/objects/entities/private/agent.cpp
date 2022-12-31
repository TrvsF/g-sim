#include "../agent.h"

namespace object
{
	Agent::Agent(GameObject* gameobject, int sides)
		: GeometryObject(gameobject, sides)
	{
		SetEntityType(GameEntityType::Agent);
	}

	void Agent::Update()
	{
		
	}
}