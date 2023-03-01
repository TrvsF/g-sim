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

	public:
		Geometry();
		Geometry(std::vector<Triangle> tris, Vector2D pos);

		void Set(Vector2D pos, int sides, float& width, float& height, Vector2D& mins, Vector2D& maxes);
		void Set(Vector2D pos, std::vector<Vector2D> points, float height, float width);

		inline const std::vector<Triangle>& Tris() const { return m_tris; }

		inline void Rotation(float rotation);
		inline float Rotation() const;

		inline void Pos(Vector2D pos);
		inline Vector2D Pos() const;
		inline Vector2D CenterPos() const;

		inline Vector2D OffsetScale()		  { return m_scaleoffset; }
		inline void OffsetScale(Vector2D pos) { m_scaleoffset = pos;  }

		inline void Active(bool active);
		inline bool Active();

		inline SDL_Color Colour()			 { return m_maincolour; }
		inline void	Colour(SDL_Color colour) { m_maincolour = colour; }

		inline void OffsetPos(Vector2D offset);
		inline void OffsetRotation(float rotation);
	};
}

#include "geometry-inl.h"

#endif // !GEOMETRY_H_