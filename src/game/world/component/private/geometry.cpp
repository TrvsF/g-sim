#include "../geometry.h"

namespace object
{
	void Geometry::set_tris(std::vector<Vector2D> points)
	{
		// get midpoiont
		float xtot = 0;
		float ytot = 0;
		int size = 0;
		for (Vector2D point : points)
		{
			xtot += point.x;
			ytot += point.y;
			size++;
		}
		Vector2D midpoint = { xtot / size, ytot / size };

		// create triangles from points
		Vector2D last = points.back();
		for (Vector2D point : points)
		{
			Triangle tri = Triangle(point, last, midpoint);
			m_tris.push_back(tri);
			last = point;
		}
	}

	Geometry::Geometry()
		: m_tris(NULL), m_pos(VEC2_ZERO), m_rotation(0), m_active(false), m_width(0), m_height(0)
	{}

	Geometry::Geometry(std::vector<Triangle> tris, Vector2D pos)
		: m_tris(tris), m_pos(pos), m_rotation(0), m_active(false), m_width(0), m_height(0)
	{}

	void Geometry::Set(Vector2D pos, int sides, float& width, float& height, Vector2D& mins, Vector2D& maxes)
	{
		// dont be silly
		if (sides < 3) { sides = 3; }
		// set width & height properly
		maxes = VEC2_ZERO;
		mins = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
		// generate random points
		std::vector<Vector2D> points;
		for (int i = 0; i < sides; i++)
		{
			float x = maths::GetRandomFloat(0, width);
			float y = maths::GetRandomFloat(0, height);
			// width & height thing
			if (maxes.x < x) { maxes.x = x; }
			if (mins.x > x) { mins.x = x; }
			if (maxes.y < y) { maxes.y = y; }
			if (mins.y > y) { mins.y = y; }

			points.push_back({ x, y });
		}

		set_tris(points);
		m_pos		  = pos;
		m_scaleoffset = VEC2_ZERO;
		m_active = true;
		m_height = height = maxes.y - mins.y;
		m_width  = width  = maxes.x - mins.x;
	}

	void Geometry::Set(Vector2D pos, std::vector<Vector2D> points, float height, float width)
	{
		set_tris(points);
		m_active	  = true;
		m_scaleoffset = VEC2_ZERO;
		m_pos		= pos;
		m_height	= height;
		m_width		= width;
	}
}