#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <SDL.h>

#include "../src/game/world/component/triangle.h"
#include "../src/util/vector2d.h"
#include "../src/util/maths.h"

#include <limits>
#include <vector>

namespace object
{
	class Geometry
	{
	protected:
		std::vector<Triangle>	m_tris;
		Vector2D				m_pos;
		Vector2D				m_scaleoffset;
		float					m_rotation;
		float					m_width;
		float					m_height;
		bool					m_active;
		SDL_Color				m_maincolour;
		SDL_Color				m_secondarycolour;

		void set_tris(std::vector<Vector2D> points);
		void normalisepoints(std::vector<Vector2D>& points, float& width, float& height);;
	public:
		Geometry();
		Geometry(std::vector<Triangle> tris, Vector2D pos);

		void Set(Vector2D pos, int sides, float& width, float& height);
		void Set(Vector2D pos, std::vector<Vector2D> points);

		inline const std::vector<Triangle>& Tris() const
		{ return m_tris; }

		inline Vector2D Size()
		{ return { m_width, m_height }; }

		inline Vector2D Offsetscale()
		{ return m_scaleoffset; }
		inline void Offsetscale(Vector2D pos)
		{ m_scaleoffset = pos;  }

		inline SDL_Color Colour()
		{ return m_maincolour; }
		inline void	Colour(SDL_Color colour)
		{ m_maincolour = colour; }

		inline void Rotation(float rotation)
		{ m_rotation = rotation; }
		inline float Rotation() const
		{ return m_rotation; }

		inline void Pos(Vector2D pos)
		{ m_pos = pos; }
		inline Vector2D Pos() const
		{ return m_pos + m_scaleoffset; }
		inline Vector2D CenterPos() const
		{ return Vector2D{ m_pos.x + (m_width / 2), m_pos.y + (m_height / 2) } + m_scaleoffset; }
		
		inline void OffsetPos(Vector2D offset)
		{ m_pos += offset; }
		inline void OffsetRotation(float rotation)
		{ m_rotation += rotation; }

		inline void Active(bool active)
		{ m_active = active; }
		inline bool Active()
		{ return m_active; }
	};
}
#endif // !GEOMETRY_H_