#ifndef FOOD_H_
#define FOOD_H_

#include "../abstract/texture-object.h"

namespace object
{
	class Food : public TextureObject
	{
	private:
		// TODO : move to setup
		int		m_hp = 25000;
		bool	m_is_being_eaten = false;
	public:
		Food(GameObject* gameobject, const char* textureid);

		void SetCollision(GameEntityType type);
		void Update();
	};
}

#endif // !FOOD_H_