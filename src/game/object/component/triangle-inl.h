#include "triangle.h"

namespace object
{
	inline Triangle Triangle::Create(Vector2D v1, Vector2D v2, Vector2D v3)
	{
		return Triangle(v1, v2, v3);
	}

	inline Vector2D Triangle::GetPoint1()
	{
		return m_v1;
	}

	inline Vector2D Triangle::GetPoint2()
	{
		return m_v2;
	}

	inline Vector2D Triangle::GetPoint3()
	{
		return m_v3;
	}
}