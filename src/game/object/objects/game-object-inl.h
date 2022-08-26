#include "game-object.h"

namespace object
{
	inline Object* GameObject::GetObject()
	{
		return m_object;
	}

	inline void GameObject::MoveForwards()
	{
		m_velocity += 1;
	}

	inline void GameObject::MoveBackwards()
	{
		m_velocity -= 1;
	}
}