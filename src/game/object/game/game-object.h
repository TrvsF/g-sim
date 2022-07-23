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

		void handle_movement();
		void handle_position();
		void reset_movement_bools();

	public:
		GameObject(Object* object = nullptr, Texture* texture = nullptr);

		bool Forward, Backward, Left, Right;

		inline Object* GetObject();
		inline Texture* GetTexture();

		inline void MoveForwards();
		inline void MoveBackwards();
		inline void TurnLeft();
		inline void TurnRight();

		void Tick();
	};
}

#include "game-object-inl.h"

#endif // !GAME-OBJECT_H_