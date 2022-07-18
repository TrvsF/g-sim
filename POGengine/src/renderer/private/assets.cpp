#include "../assets.h"

namespace renderer
{
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

	void Assets::SetTexture(const char* path_to_texture, SDL_Texture* texture)
	{
		m_textures[path_to_texture] = texture;
	}

	SDL_Texture* Assets::GetTexture(const char* path_to_texture)
	{
		return m_textures[path_to_texture];
	}
}