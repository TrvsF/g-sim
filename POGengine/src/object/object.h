#ifndef OBJECT_H_
#define OBJECT_H_

#include "aabb.h"
#include "transform.h"

namespace object
{
	class Object
	{
	private:


		AABB		m_aabb;
		Transform	m_transform;
	};
}

#endif