#ifndef AABB_H_
#define AABB_H_

#include "../src/util/vector2d.h"
#include "../src/util/vector3d.h"
#include "../src/util/size.h"

namespace object
{
	class AABB
	{
	private:
		explicit AABB(const Vector3D pos = VEC3_ZERO, const Size size = SIZE_ZERO);
	public:
		inline static AABB Create(const Vector3D pos = VEC3_ZERO, const Size size = SIZE_ZERO);

		inline float GetMinX() const;
		inline float GetMinY() const;
		inline float GetMinZ() const;

		inline float GetMaxX() const;
		inline float GetMaxY() const;
		inline float GetMaxZ() const;

		inline Size GetSize() const;
		inline void SetSize(Size size);

		inline Vector3D GetPos() const;
		inline Vector3D GetMidpoint() const;
		inline void SetPos(Vector3D pos);
		inline void OffsetPos(Vector3D offset);
		
		inline bool IntersectsRect2D(const AABB& other) const;
		inline bool IntersectsPoint(Vector2D point) const;
		inline bool IntersectsPoint(int x, int y) const;

		static const AABB ZERO;
	protected:
		Size m_size;
		Vector3D m_pos;
	};
}

#include "aabb-inl.h"

#endif // !AABB_H_