#include "aabb.h"

namespace object
{
	inline AABB AABB::Create(const Vector3D origin, const Size size)
	{
		return AABB(origin, size);
	}

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

	inline Size AABB::GetSize() const
	{
		return m_size;
	}

	inline void AABB::SetSize(Size size)
	{
		m_size = size;
	}

	inline Vector3D AABB::GetOrigin() const
	{
		return m_origin;
	}

	inline void AABB::SetOrigin(Vector3D origin)
	{
		m_origin = origin;
	}

	inline void AABB::OffsetOrigin(Vector3D offset)
	{
		m_origin += offset;
	}

	inline bool AABB::IntersectsRect2D(const AABB& other) const
	{
		return !(GetMaxX() < other.GetMinX() ||
			other.GetMaxX() < GetMinX() ||
			GetMaxY() < other.GetMinY() ||
			other.GetMaxY() < GetMinY());
	}
}