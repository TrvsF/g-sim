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
		: m_tris(NULL), m_pos(VEC2_ZERO), m_rotation(0), m_active(false)
	{}

	Geometry::Geometry(std::vector<Triangle> tris, Vector2D pos)
		: m_tris(tris), m_pos(pos), m_rotation(0), m_active(false)
	{}

	void Geometry::Set(Vector2D pos, int sides, float width, float height)
	{
		// dont be silly
		if (sides < 3) { sides = 3; }
		// generate random points
		std::vector<Vector2D> points;
		for (int i = 0; i < sides; i++)
		{
			points.push_back({ maths::GetRandomFloat(0, width), maths::GetRandomFloat(0, height) });
		}

		set_tris(points);
		m_pos		= pos;
		m_active	= true;
	}

	void Geometry::Set(Vector2D pos, std::vector<Vector2D> points)
	{
		set_tris(points);
		m_active	= true;
		m_pos		= pos;
	}
}
