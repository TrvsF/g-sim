#include "triangle.h"

namespace object
{
	inline Triangle Triangle::Create(Vector2D v1, Vector2D v2, Vector2D v3)
	{
		return Triangle(v1, v2, v3);
	}

	inline std::vector<SDL_Vertex> Triangle::GetVerts()
	{
		return
		{
			{ SDL_FPoint{ m_v1.x, m_v1.y }, SDL_Color{ 255, 0, 0, 255 } },
			{ SDL_FPoint{ m_v2.x, m_v2.y }, SDL_Color{ 0, 0, 255, 255 } },
			{ SDL_FPoint{ m_v3.x, m_v3.y }, SDL_Color{ 0, 255, 0, 255 } }
		};
	}
}