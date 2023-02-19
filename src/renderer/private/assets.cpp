#include "../assets.h"

namespace renderer
{
	Assets::Assets()
	{
		m_assetpath = file::GetBasePath() + "assets/";
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

	void Assets::SetFont(std::string full_path, TTF_Font* font)
	{
		m_fonts[full_path] = font;
	}

	TTF_Font* Assets::GetFont(std::string full_path)
	{
		return m_fonts[full_path];
	}

	std::string Assets::GetPathToTexture(const char* path_to_texture)
	{
		std::string path = m_assetpath + "textures/" + std::string(path_to_texture);
		return path;
	}

	std::string Assets::GetFullTexturePath()
	{
		return m_assetpath + "textures/";
		
	}

	std::string Assets::GetFullFontPath()
	{
		return m_assetpath + "fonts/";
	}
}