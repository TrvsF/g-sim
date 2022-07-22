#include "game-object.h"

namespace object
{
	inline void GameObject::MoveForwards()
	{
		m_velocity += 1;
	}
}