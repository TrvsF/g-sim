#include "../assets.h"

namespace renderer
{
	Assets::Assets()
	{
		m_asset_path = SDL_GetBasePath() + std::string("assets/");
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

	void Assets::SetTexture(std::string full_path, SDL_Texture* texture)
	{
		m_textures[full_path] = texture;
	}

	SDL_Texture* Assets::GetTexture(std::string full_path)
	{
		return m_textures[full_path];
	}

	std::string Assets::GetFullPath(const char* path_to_texture)
	{
		std::string path = m_asset_path + std::string(path_to_texture);
		return path;
	}

}