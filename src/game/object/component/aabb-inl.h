#include "aabb.h"

namespace object
{
	inline AABB AABB::Create(const Vector3D pos, const Size size)
	{
		return AABB(pos, size);
	}

	inline float AABB::GetMaxX() const
	{
		return m_pos.x + m_size.width;
	}

	inline float AABB::GetMaxY() const
	{
		return m_pos.y + m_size.height;
	}

	inline float AABB::GetMaxZ() const
	{
		return m_pos.z + m_size.depth;
	}

	inline float AABB::GetMinX() const
	{
		return m_pos.x;
	}

	inline float AABB::GetMinY() const
	{
		return m_pos.y;
	}

	inline float AABB::GetMinZ() const
	{
		return m_pos.z;
	}

	inline Size AABB::GetSize() const
	{
		return m_size;
	}

	inline void AABB::SetSize(Size size)
	{
		m_size = size;
	}

	inline Vector3D AABB::GetPos() const
	{
		return m_pos;
	}

	inline Vector3D AABB::GetMidpoint() const
	{
		return { m_pos.x + (m_size.width / 2.0f), m_pos.y + (m_size.height / 2.0f), (m_pos.z + m_size.depth / 2.0f) };
	}

	inline void AABB::SetPos(Vector3D pos)
	{
		m_pos = pos;
	}

	inline void AABB::OffsetPos(Vector3D offset)
	{
		m_pos += offset;
	}

	inline bool AABB::IntersectsRect2D(const AABB& other) const
	{
		return !(GetMaxX() < other.GetMinX() ||
			other.GetMaxX() < GetMinX() ||
			GetMaxY() < other.GetMinY() ||
			other.GetMaxY() < GetMinY());
	}
}