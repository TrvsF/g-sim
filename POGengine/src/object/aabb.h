#ifndef AABB_H_
#define AABB_H_

#include "../util/vector3d.h"
#include "../util/size.h"

namespace object
{
	class AABB
	{
	private:
		explicit AABB(const Vector3D origin = VEC3_ZERO, const Size size = SIZE_ZERO);
	public:
		inline static AABB Create(const Vector3D origin = VEC3_ZERO, const Size size = SIZE_ZERO);

		inline float GetMinX() const;
		inline float GetMinY() const;
		inline float GetMinZ() const;

		inline float GetMaxX() const;
		inline float GetMaxY() const;
		inline float GetMaxZ() const;

		inline Size GetSize() const;
		inline void SetSize(Size size);

		inline Vector3D GetOrigin() const;
		inline void SetOrigin(Vector3D origin);

		inline bool IntersectsRect2D(const AABB& other) const;

		static const AABB ZERO;
	protected:
		Size m_size;
		Vector3D m_origin;
	};
}

#include "aabb-inl.h"

#endif // !AABB_H_