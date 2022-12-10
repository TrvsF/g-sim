#ifndef FOOD_H_
#define FOOD_H_

#include "abs/texture-object.h"

namespace object
{
	class Food : public TextureObject
	{
	private:
		
	public:
		Food(GameObject* gameobject, const char* textureid);

		void Update();
	};
}

#endif // !FOOD_H_