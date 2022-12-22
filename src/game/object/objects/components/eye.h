#ifndef EYE_H_
#define EYE_H_

#include "../abstract/geometry-object.h"

namespace object
{
	class Eye : public Geometry
	{
	private:
		int m_maxdistance;
		int m_fov;
	public:
	};
}

#endif // EYE_H_