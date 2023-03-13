#include "transform.h"

namespace object
{
	inline Transform Transform::Create(Vector3D position, Vector3D rotation)
	{
		return Transform(position, rotation);
	}

	inline const Vector3D Transform::GetPosition() const
	{
		return m_position;
	}

	inline const Vector2D Transform::Get2DPosition() const
	{
		return { m_position.x, m_position.y };
	}

	inline void Transform::SetPosition(Vector3D position)
	{
		m_position = position;
	}

	inline void Transform::OffsetPosition(Vector3D offset)
	{
		m_position += offset;
	}

	inline int Transform::GetRotation()
	{
		int r = m_rotation.z;
		maths::GetBoundedAngleDeg(r);
		return r;
	}

	inline void Transform::SetRotation(Vector3D rotation)
	{
		m_rotation = rotation;
	}

	inline void Transform::OffsetRotation(Vector3D offset)
	{
		m_rotation += offset;
	}
}