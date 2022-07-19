#ifndef AABB_H_
#define AABB_H_

#include "../util/vector3d.h"
#include "../util/size.h"

namespace object
{
	class AABB
	{
	private:
		Size m_size;
		Vector3D m_origin;

	public:
		explicit AABB(float x = 0, float y = 0, float z = 0, float width = 0, float height = 0, float depth = 0);
		explicit AABB(const Vector3D& origin = VEC3_ZERO, const Size& size = SIZE_ZERO);

		inline void Set2D(float x, float y, float width, float height);

		inline float GetMinX() const;
		inline float GetMinY() const;
		inline float GetMinZ() const;

		inline float GetMaxX() const;
		inline float GetMaxY() const;
		inline float GetMaxZ() const;

		inline bool IntersectsRect2D(const AABB& other) const;
	};
}

#include "aabb-inl.h"

#endif // !AABB_H_