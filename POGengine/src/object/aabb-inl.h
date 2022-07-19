#include "aabb.h"

namespace object
{
	inline float AABB::GetMaxX() const
	{
		return m_origin.x + m_size.width;
	}

	inline float AABB::GetMaxY() const
	{
		return m_origin.y + m_size.height;
	}

	inline float AABB::GetMaxZ() const
	{
		return m_origin.z + m_size.depth;
	}

	inline float AABB::GetMinX() const
	{
		return m_origin.x;
	}

	inline float AABB::GetMinY() const
	{
		return m_origin.y;
	}

	inline float AABB::GetMinZ() const
	{
		return m_origin.z;
	}

	inline bool AABB::IntersectsRect2D(const AABB& other) const
	{
		return !(GetMaxX() < other.GetMinX() ||
			other.GetMaxX() < GetMinX() ||
			GetMaxY() < other.GetMinY() ||
			other.GetMaxY() < GetMinY());
	}

	inline void AABB::Set2D(float x, float y, float width, float height)
	{
		m_origin.x = x;
		m_origin.y = y;
		m_size.width = width;
		m_size.height = height;
	}
}