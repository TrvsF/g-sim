#include "geometry-object.h"

namespace object
{
	inline std::vector<Triangle*> GeometryObject::GetTris()
	{
		return m_tris;
	}
}