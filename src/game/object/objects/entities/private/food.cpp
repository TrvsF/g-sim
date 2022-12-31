#include "../food.h"

namespace object
{
	Food::Food(GameObject* gameobject, const char* textureid)
		: TextureObject(gameobject, textureid)
	{
		SetEntityType(GameEntityType::Food);
	}

	void Food::Update()
	{
		if (m_is_being_eaten)
		{
			float scale = GetTexture()->Scale();
			scale -= 0.005f;
	
			GetTexture()->Scale(scale);
		}

		m_is_being_eaten = false;
	}

	void Food::SetCollision(GameEntityType type)
	{
		switch (type)
		{
			case GameEntityType::Player:
				m_is_being_eaten = true;
				break;
			default:
				break;
		}
	}
}