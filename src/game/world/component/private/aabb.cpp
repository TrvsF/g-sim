#include "../aabb.h"

namespace object
{
	const AABB AABB::ZERO;

	AABB::AABB(const Vector3D pos, const Size size)
		: m_pos(pos), m_size(size)
	{}
}