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

	inline void Transform::SetPosition(Vector3D position)
	{
		m_position = position;
	}

	inline void Transform::OffsetPosition(Vector3D offset)
	{
		m_position += offset;
	}

	inline const Vector3D Transform::GetRotation() const
	{
		return m_rotation;
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