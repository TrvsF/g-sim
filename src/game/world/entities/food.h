#ifndef FOOD_H_
#define FOOD_H_

#include "../src/game/world/objects/texture-object.h"
#include <vector>

namespace object
{
	class Food : public TextureObject
	{
	private:
		std::vector<GameObject*> m_collidingobjects;
		int m_ammount;

		void setup();
	public:
		Food(GameObject* gameobject, int ammount);

		inline void AddCollidingObject(GameObject* object)
		{ m_collidingobjects.push_back(object); }
		void Update();
	};
}

#endif // !FOOD_H_