#include "geometry-object.h"

namespace object
{
	inline float GeometryObject::Rotate()
	{
		return m_rotate;
	}
	
	inline void GeometryObject::Rotate(float rotate)
	{
		m_rotate = rotate;
	}
}