#include "triangle.h"

namespace object
{
	inline bool Triangle::IsPointInTri(Vector2D point)
	{
		float s1 = m_v3.y - m_v1.y;
		float s2 = m_v3.x - m_v1.x;
		float s3 = m_v2.y - m_v1.y;
		float s4 = point.y - m_v1.y;

		float w1 = (m_v1.x * s1 + s4 * s2 - point.x * s1) / (s3 * s2 - (m_v2.x - m_v1.x) * s1);
		float w2 = (s4 - w1 * s3) / s1;
		return w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1;

		//https://github.com/SebLague/Gamedev-Maths/blob/master/PointInTriangle.cs
	}
}