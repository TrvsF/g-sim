#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <SDL.h>
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

		explicit Triangle(Vector2D v1 = VEC2_ZERO, Vector2D v2 = VEC2_ZERO, Vector2D v3 = VEC2_ZERO);
	public:
		Triangle(Triangle const& origin)
			: m_v1(origin.m_v1), m_v2(origin.m_v2), m_v3(origin.m_v3)
		{}
		inline static Triangle Create(Vector2D v1 = VEC2_ZERO, Vector2D v2 = VEC2_ZERO, Vector2D v3 = VEC2_ZERO);

		inline Vector2D GetPoint1();
		inline Vector2D GetPoint2();
		inline Vector2D GetPoint3();
	};
}

#include "triangle-inl.h"

#endif // !TRIANGLE_H_