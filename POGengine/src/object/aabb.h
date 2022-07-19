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
		AABB(float x = 0, float y = 0, float z = 0, float width = 0, float height = 0, float depth = 0)
			: m_origin(x, y, z), m_size(width, height, depth) {}

		void Set2D(float x, float y, float width, float height);

		float GetMinX() const;
		float GetMinY() const;
		float GetMinZ() const;

		float GetMaxX() const;
		float GetMaxY() const;
		float GetMaxZ() const;

		bool IntersectsRect2D(const AABB& other) const;
	};
}
#endif // !AABB_H_