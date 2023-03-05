#include "../food.h"

namespace object
{
	Food::Food(GameObject* gameobject, int ammount)
		: TextureObject(gameobject, "food-full", 10, 64)
	{
		m_ammount = ammount;
		setup();
	}

	Food::~Food()
	{

	}

	void Food::setup()
	{
		SetEntityType(GameEntityType::Food);
	}

	int Food::Eat()
	{
		int start = m_ammount;
		m_ammount -= 10;
		if (m_ammount < 0)
		{
			die();
			return start;
		}
		return 100;
	}

	void Food::Update()
	{
		
	}
}