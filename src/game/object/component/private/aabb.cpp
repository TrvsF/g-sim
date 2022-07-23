#include "../aabb.h"

namespace object
{
	const AABB AABB::ZERO;

	AABB::AABB(const Vector3D origin, const Size size)
		: m_origin(origin), m_size(size)
	{}
}