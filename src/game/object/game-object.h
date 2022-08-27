#ifndef OBJECT_H_
#define OBJECT_H_

#include "component/aabb.h"
#include "component/transform.h"

namespace object
{
	class GameObject
	{
	private:
		AABB		m_aabb;
		Transform	m_transform;

	public:
		GameObject(AABB aabb, Transform transform)
			: m_aabb(aabb), m_transform(transform)
		{}
		GameObject(GameObject* gameobject)
			: m_aabb(gameobject->GetAABB()), m_transform(gameobject->GetTransform())
		{}

		inline static GameObject* Create(Vector3D position, Vector3D rotation, Size size);

		inline Transform& GetTransform();
		inline void SetTransform(Transform& transform);

		inline AABB& GetAABB();
		inline void SetAABB(AABB& aabb);

		inline const Vector3D GetPosition() const;
		inline void SetPosition(Vector3D position);

		inline const Size GetSize() const;
		inline void SetSize(Size size);

		inline void Tick();
		inline GameObject* GetObject();
	};
}

#include "game-object-inl.h"

#endif