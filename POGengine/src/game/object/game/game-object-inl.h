#include "game-object.h"

namespace object
{
	inline Object* GameObject::GetObject()
	{
		return m_object;
	}

	inline Texture* GameObject::GetTexture()
	{
		return m_texture;
	}

	inline void GameObject::MoveForwards()
	{
		m_velocity += 1;
	}
}