#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../src/renderer/renderer.h"
#include "../component/object.h"
#include "../component/texture.h"

namespace object
{
	class GameObject
	{
	protected:
		Object* m_object;

	private:
		float m_velocity;

		void handle_movement();
		void handle_position();
		void reset_movement_bools();

	public:
		// GameObject(Object* object = nullptr, Texture* texture = nullptr);
		GameObject(Object* object);

		bool Forward, Backward, Left, Right;

		inline Object* GetObject();

		inline void MoveForwards();
		inline void MoveBackwards();
		inline void TurnLeft();
		inline void TurnRight();

		void Tick();
	};
}

#include "game-object-inl.h"

#endif // !GAME-OBJECT_H_