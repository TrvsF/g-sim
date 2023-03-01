#include "../food.h"

namespace object
{
	Food::Food(GameObject* gameobject, int ammount)
		: TextureObject(gameobject, "food")
	{
		m_ammount = ammount;
		setup();
	}

	void Food::setup()
	{
		SetEntityType(GameEntityType::Food);
	}

	void Food::Update()
	{
		if (!m_collidingobjects.empty())
		{
			// TODO : be eaten
		}
		m_collidingobjects.clear();
	}
}