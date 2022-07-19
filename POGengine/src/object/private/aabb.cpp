#include "../aabb.h"

namespace object
{
	float AABB::GetMaxX() const
	{
		return m_origin.x + m_size.width;
	}

	float AABB::GetMaxY() const
	{
		return m_origin.y + m_size.height;
	}

	float AABB::GetMaxZ() const
	{
		return m_origin.z + m_size.depth;
	}

	bool AABB::IntersectsRect2D(const AABB& other) const
	{
		return !(GetMaxX() < other.GetMinX() ||
			other.GetMaxX() < GetMinX() ||
			GetMaxY() < other.GetMinY() ||
			other.GetMaxY() < GetMinY());
	}

	void AABB::Set2D(float x, float y, float width, float height)
	{
		m_origin.x = x;
		m_origin.y = y;
		m_size.width = width;
		m_size.height = height;
	}

	float AABB::GetMinX() const
	{
		return m_origin.x;
	}

	float AABB::GetMinY() const
	{
		return m_origin.y;
	}

	float AABB::GetMinZ() const
	{
		return m_origin.z;
	}
	
}