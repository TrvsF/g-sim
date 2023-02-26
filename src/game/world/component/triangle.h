#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../src/util/vector2d.h"
#include <vector>

namespace object
{
	class Triangle
	{
	private:
		Vector2D m_v1;
		Vector2D m_v2;
		Vector2D m_v3;
	public:
		Triangle(const Vector2D v1 = VEC2_ZERO, const Vector2D v2 = VEC2_ZERO, const Vector2D v3 = VEC2_ZERO)
			: m_v1(v1), m_v2(v2), m_v3(v3)
		{}

		inline bool IsPointInTri(Vector2D point)
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

		inline Vector2D GetPoint1() const { return m_v1; }
		inline Vector2D GetPoint2() const { return m_v2; }
		inline Vector2D GetPoint3() const { return m_v3; }
		inline std::vector<Vector2D> GetPoints() const { return { m_v1, m_v2, m_v3 }; }
	};
}

#include "triangle-inl.h"

#endif // !TRIANGLE_H_