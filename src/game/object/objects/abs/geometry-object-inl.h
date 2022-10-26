#include "geometry-object.h"

namespace object
{
	inline Vector2D GeometryObject::Sides()
	{
		return Vector2D{ m_side1, m_side2 };
	}

	inline void GeometryObject::Sides(Vector2D sides) 
	{
		m_side1 = sides.x;
		m_side2 = sides.y;
	}

	inline float GeometryObject::Rotate()
	{
		return m_rotate;
	}
	
	inline void GeometryObject::Rotate(float rotate)
	{
		m_rotate = rotate;
	}
}