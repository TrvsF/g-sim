#include "object.h"

namespace object
{
	inline Object* Object::Create(Vector3D position, Vector3D rotation, Size size)
	{
		return new Object(AABB::Create(position, size), Transform::Create(position, rotation));
	}

	inline Transform& Object::GetTransform()
	{
		return m_transform;
	}

	inline void Object::SetTransform(Transform& transform)
	{
		m_transform = transform;
	}

	inline AABB& Object::GetAABB()
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