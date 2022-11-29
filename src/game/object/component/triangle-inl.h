#include "triangle.h"

namespace object
{
	inline Triangle Triangle::Create(const Vector2D v1, const Vector2D v2, const  Vector2D v3)
	{
		return Triangle(v1, v2, v3);
	}

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