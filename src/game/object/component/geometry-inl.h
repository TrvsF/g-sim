#include "geometry.h"

namespace object
{
	inline void Geometry::Rotation(float rotation)
	{
		m_rotation = rotation;
	}

	inline float Geometry::Rotation() const
	{
		return m_rotation;
	}

	inline void Geometry::Pos(Vector2D pos)
	{
		m_pos = pos;
	}

	inline Vector2D Geometry::Pos() const
	{
		return m_pos;
	}

	inline void Geometry::OffsetPos(Vector2D offset)
	{
		m_pos += offset;
	}

	inline void Geometry::OffsetRotation(float rotation)
	{
		m_rotation += rotation;
	}

	inline void Geometry::Active(bool active)
	{
		m_active = active;
	}

	inline bool Geometry::Active()
	{
		return m_active;
	}
}