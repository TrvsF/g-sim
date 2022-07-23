#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../src/util/vector3d.h"

namespace object
{
	class Transform
	{
	private:
		explicit Transform(Vector3D position = VEC3_ZERO, Vector3D rotation = VEC3_ZERO);
	public:
		inline static Transform Create(Vector3D position = VEC3_ZERO, Vector3D rotation = VEC3_ZERO);

		inline const Vector3D GetPosition() const;
		inline void SetPosition(Vector3D position);
		inline void OffsetPosition(Vector3D offset);

		inline const Vector3D GetRotation() const;
		inline void SetRotation(Vector3D rotation);
		inline void OffsetRotation(Vector3D offset);

		static const Transform ZERO;
	protected:
		Vector3D m_position;
		Vector3D m_rotation;
	};
}

#include "transform-inl.h"

#endif // !TRANSFORM_H_