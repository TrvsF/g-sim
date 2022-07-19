#include "../aabb.h"

namespace object
{
	AABB::AABB(float x, float y, float z, float width, float height, float depth)
		: m_origin(x, y, z), m_size(width, height, depth)
	{}

	AABB::AABB(const Vector3D& origin, const Size& size)
		: m_origin(origin), m_size(size)
	{}
}