#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../src/renderer/renderer.h"
#include "../object.h"
#include "../component/texture.h"

namespace object
{
	class GameObject
	{
	protected:
		Object* m_object;
	private:

	public:
		GameObject(Object* object);

		inline Object* GetObject();

		void Tick();
	};
}

#include "game-object-inl.h"

#endif // !GAME-OBJECT_H_