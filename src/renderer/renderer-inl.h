#include "renderer.h"

namespace renderer
{
	inline SDL_Renderer* Renderer::GetRendererObj()
	{
		return Renderer::m_renderer;
	}

	inline Vector2D Renderer::GetScreensize()
	{
		return { (float)m_width, (float)m_height };
	}

	inline void Renderer::add_texture_object(object::Texture* texture_object)
	{
		m_texutre_objects.push_back(texture_object);
	}
}