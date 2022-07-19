#include "../transform.h"

namespace object
{
	Transform::Transform(Vector3D position, Vector3D rotation, Vector3D scale)
		: m_position(position), m_rotation(rotation), m_scale(scale)
	{}
}