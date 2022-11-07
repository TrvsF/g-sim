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

		explicit Triangle(Vector2D v1 = VEC2_ZERO, Vector2D v2 = VEC2_ZERO, Vector2D v3 = VEC2_ZERO);
	public:
		inline static Triangle Create(Vector2D v1 = VEC2_ZERO, Vector2D v2 = VEC2_ZERO, Vector2D v3 = VEC2_ZERO);
	};
}

#endif // !TRIANGLE_H_