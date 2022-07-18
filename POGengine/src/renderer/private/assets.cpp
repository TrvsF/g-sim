#include "../assets.h"

namespace renderer
{
	Assets* Assets::s_instance = nullptr;

	Assets::Assets()
	{
		
	}

	Assets::~Assets()
	{
		for (const auto &texture : m_textures)
		{
			if (texture.second != NULL)
			{
				SDL_DestroyTexture(texture.second);
			}
		}
		m_textures.clear();
	}

	void Assets::Create()
	{
		if (!s_instance)
		{
			s_instance = new Assets();
		}
	}

	Assets* Assets::Get()
	{
		return Assets::s_instance;
	}

	void Assets::Destroy()
	{
		SAFE_DELETE(s_instance);
	}

	SDL_Texture* Assets::GetTexture(const char* path_to_texture)
	{
		if (m_textures[path_to_texture] == nullptr)
		{
			m_textures[path_to_texture] = Renderer::Get()->LoadTexture(path_to_texture);
		}

		return m_textures[path_to_texture];
	}
}