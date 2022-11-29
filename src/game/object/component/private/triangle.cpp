#include "../triangle.h"

namespace object
{
	const Triangle Triangle::ZERO;

	Triangle::Triangle(SDL_FPoint v1, SDL_FPoint v2, SDL_FPoint v3)
		: m_v1(v1), m_v2(v2), m_v3(v3)
	{}
}