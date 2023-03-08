#include "../food.h"

namespace object
{
	Food::Food(GameObject* gameobject, int ammount)
		: TextureObject(gameobject, "food-full", 10)
	{
		m_maxammount	= ammount;
		m_ammount		= ammount;

		GetTexture()->CurrentXFrame(0);
		GetTexture()->CurrentYFrame(-64 );
		setup();
	}

	Food::~Food()
	{

	}

	void Food::setup()
	{
		SetEntityType(GameEntityType::Food);
	}

	void Food::die()
	{
		bus->postpone(event::eObjectDeath { this });
		bus->process(); 
		GetTexture()->Active(false);
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
		int iammount = round(m_maxammount / 10);
		int framecount = 0;
		for (int i = m_maxammount; i > 0; i -= iammount)
		{
			if (m_ammount >= i)
			{
				if (framecount != 0)
				{ GetTexture()->CurrentYFrame(0); }
				GetTexture()->CurrentXFrame(framecount);
				break;
			}
			framecount++;
		}
	}
}