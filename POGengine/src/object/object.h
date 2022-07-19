#ifndef OBJECT_H_
#define OBJECT_H_

#include "../util/vector2d.h"
#include "../util/rect.h"

namespace object
{
	enum class Type
	{
		Player,
		Right,
		Middle,
		Back,
		Forward
	};

	class Object
	{
	protected:
		Rect		m_rect;
	private:
		float		m_rotation;
		Vector2D	m_pos;
	};
}

#endif