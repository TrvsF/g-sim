#ifndef FOOD_H_
#define FOOD_H_

#include "../src/game/world/objects/texture-object.h"

#include <vector>

namespace object
{
	class Food : public TextureObject
	{
	private:
		int m_maxammount;
		int m_ammount;

		void die();
		
		void setup();
	public:
		Food(GameObject* gameobject, int id, int ammount);
		Food(GameObject* gameobject, int ammount);
		~Food();

		int Eat();

		void Update();
	};
}
#endif // !FOOD_H_