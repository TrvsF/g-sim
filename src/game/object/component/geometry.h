#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <SDL.h>

#include "../src/game/object/component/triangle.h"
#include "../src/util/vector2d.h"
#include "../src/util/maths.h"
#include <vector>

namespace object
{
	class Geometry
	{
	protected:
		std::vector<Triangle>	m_tris;
		Vector2D				m_pos;
		float					m_rotation;
		bool					m_active;

		void set_tris(std::vector<Vector2D> points);

	public:
		Geometry();
		Geometry(std::vector<Triangle> tris, Vector2D pos);

		void Set(Vector2D pos, int sides, float width, float height);
		void Set(Vector2D pos, std::vector<Vector2D> points);

		inline const std::vector<Triangle>& Tris() const { return m_tris; }

		inline void Rotation(float rotation);
		inline float Rotation() const;

		inline void Pos(Vector2D pos);
		inline Vector2D Pos() const;

		inline void Active(bool active);
		inline bool Active();

		inline void OffsetPos(Vector2D offset);
	};
}

#include "geometry-inl.h"

#endif // !GEOMETRY_H_