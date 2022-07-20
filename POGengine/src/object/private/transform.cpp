#include "../transform.h"

namespace object
{
	const Transform Transform::ZERO;

	Transform::Transform(Vector3D position, Vector3D rotation)
		: m_position(position), m_rotation(rotation)
	{}
}