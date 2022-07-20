#include "object.h"

namespace object
{
	inline Object* Object::Create(const AABB& aabb, const Transform& transform)
	{
		return new Object(aabb, transform);
	}

	inline const Transform& Object::GetTransform() const
	{
		return m_transform;
	}

	inline void Object::SetTransform(Transform& transform)
	{
		m_transform = transform;
	}

	inline const AABB& Object::GetAABB() const
	{
		return m_aabb;
	}

	inline void Object::SetAABB(AABB& aabb)
	{
		m_aabb = aabb;
	}

	inline const Vector3D Object::GetPosition() const
	{
		return m_transform.GetPosition();
	}

	inline void Object::SetPosition(Vector3D position)
	{
		m_transform.SetPosition(position);
	}

	inline const Size Object::GetSize() const
	{
		return m_aabb.GetSize();
	}

	inline void Object::SetSize(Size size)
	{
		m_aabb.SetSize(size);
	}
}