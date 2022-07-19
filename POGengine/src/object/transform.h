#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../util/vector3d.h"

namespace object
{
	class Transform
	{
	public:
		explicit Transform(Vector3D position = VEC3_ZERO, Vector3D rotation = VEC3_ZERO, Vector3D scale = VEC3_ZERO);
	protected:
		Vector3D m_position;
		Vector3D m_rotation;
		Vector3D m_scale;
	};
}

#endif // !TRANSFORM_H_