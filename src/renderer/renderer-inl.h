#include "renderer.h"

namespace renderer
{
	inline Renderer* Renderer::Get()
	{
		return Renderer::s_instance;
	}

	inline SDL_Renderer* Renderer::GetRendererObj()
	{
		return Renderer::m_renderer;
	}
}