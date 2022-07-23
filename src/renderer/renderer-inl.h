#include "renderer.h"

namespace renderer
{
	inline Renderer* Renderer::Get()
	{
		return Renderer::s_instance;
	}
}