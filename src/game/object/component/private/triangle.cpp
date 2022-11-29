#include "../triangle.h"

namespace object
{
	const Triangle Triangle::ZERO;

	Triangle::Triangle(const Vector2D v1, const Vector2D v2, const Vector2D v3)
		: m_v1(v1), m_v2(v2), m_v3(v3)
	{}
}