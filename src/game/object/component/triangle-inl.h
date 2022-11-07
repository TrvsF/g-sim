#include "triangle.h"

namespace object
{
	inline Triangle Triangle::Create(Vector2D v1, Vector2D v2, Vector2D v3)
	{
		return Triangle(v1, v2, v3);
	}
}