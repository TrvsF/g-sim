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
		m_texutreobjects.push_back(texture_object);
	}

	inline void Renderer::remove_texture_object(object::Texture* texture_object)
	{
		std::vector<object::Texture*>::iterator pos = std::find(m_texutreobjects.begin(), m_texutreobjects.end(), texture_object);
		if (pos != m_texutreobjects.end()) { m_texutreobjects.erase(pos); }
	}
}