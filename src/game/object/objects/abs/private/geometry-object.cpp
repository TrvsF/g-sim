#include "../geometry-object.h"

namespace object
{
	GeometryObject::GeometryObject(GameObject* object)
		: GameObject(object)
	{
		m_tris.push_back(Triangle::Create({ 50, 50 }, { 60, 100 }, {70, 70}));

		m_rotate = 0;
		m_debug = true;

		renderer::Renderer::Get()->AddVerts(GetVert());
	}

	std::vector<SDL_Vertex> GeometryObject::GetVert()
	{
		return { { SDL_FPoint{ 400, 150 }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ 200, 450 }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ 600, 450 }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, }, };
	}
}