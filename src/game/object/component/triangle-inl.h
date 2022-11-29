#include "triangle.h"

namespace object
{
	inline Triangle Triangle::Create(Vector2D v1, Vector2D v2, Vector2D v3)
	{
		return Triangle({v1.x, v1.y}, {v2.x, v2.y}, { v3.x, v3.y });
	}

	inline SDL_FPoint Triangle::GetPoint1()
	{
		return m_v1;
	}

	inline SDL_FPoint Triangle::GetPoint2()
	{
		return m_v2;
	}

	inline SDL_FPoint Triangle::GetPoint3()
	{
		return m_v3;
	}
}