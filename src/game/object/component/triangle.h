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

		inline Vector2D GetPoint1() const;
		inline Vector2D GetPoint2() const;
		inline Vector2D GetPoint3() const;
		inline std::vector<Vector2D> GetPoints() const
		{
			return { m_v1, m_v2, m_v3 };
		}
	};
}

#include "triangle-inl.h"

#endif // !TRIANGLE_H_