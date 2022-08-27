#ifndef OBJECT_H_
#define OBJECT_H_

#include "component/aabb.h"
#include "component/transform.h"

namespace object
{
	class Object
	{
	private:
		AABB		m_aabb;
		Transform	m_transform;

		explicit Object(const AABB& aabb = AABB::ZERO, const Transform& transform = Transform::ZERO)
			: m_transform(transform), m_aabb(aabb)
		{}
	public:
		inline static Object* Create(Vector3D position, Vector3D rotation, Size size);

		inline Transform& GetTransform();
		inline void SetTransform(Transform& transform);

		inline AABB& GetAABB();
		inline void SetAABB(AABB& aabb);

		inline const Vector3D GetPosition() const;
		inline void SetPosition(Vector3D position);

		inline const Size GetSize() const;
		inline void SetSize(Size size);

	};
}

#include "object-inl.h"

#endif