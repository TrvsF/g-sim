#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <SDL_rect.h>
#include "../src/util/vector2d.h"
#include <vector>

namespace object
{
	class Triangle
	{
	private:
		SDL_FPoint m_v1;
		SDL_FPoint m_v2;
		SDL_FPoint m_v3;

		
	public:
		explicit Triangle(SDL_FPoint v1 = { 0, 0 }, SDL_FPoint v2 = { 0, 0 }, SDL_FPoint v3 = { 0, 0 });
		Triangle(Triangle const& origin)
			: m_v1(origin.m_v1), m_v2(origin.m_v2), m_v3(origin.m_v3)
		{}
		inline static Triangle Create(Vector2D v1 = { 0, 0 }, Vector2D v2 = { 0, 0 }, Vector2D v3 = { 0, 0 });

		inline SDL_FPoint GetPoint1();
		inline SDL_FPoint GetPoint2();
		inline SDL_FPoint GetPoint3();

		static const Triangle ZERO;
	};
}

#include "triangle-inl.h"

#endif // !TRIANGLE_H_