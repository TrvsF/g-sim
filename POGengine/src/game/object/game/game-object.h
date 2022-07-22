#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../component/object.h"
#include "../component/texture.h"

namespace object
{
	class GameObject
	{
	private:
		Object*		m_object;
		Texture*	m_texture;

		float m_velocity;

	public:
		GameObject(Object* object = nullptr, Texture* texture = nullptr);

		inline void MoveForwards();
		inline void MoveBackwards();
		inline void TurnLeft();
		inline void TurnRight();
	};
}

#include "game-object-inl.h"

#endif // !GAME-OBJECT_H_