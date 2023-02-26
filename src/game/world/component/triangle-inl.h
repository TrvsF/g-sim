#include "triangle.h"

namespace object
{
	inline Vector2D Triangle::GetPoint1() const
	{
		return m_v1;
	}

	inline Vector2D Triangle::GetPoint2() const
	{
		return m_v2;
	}

	inline Vector2D Triangle::GetPoint3() const
	{
		return m_v3;
	}
}